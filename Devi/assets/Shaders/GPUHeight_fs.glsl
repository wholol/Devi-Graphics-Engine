#version 460 core

in float height;
out vec4 fragColor;

in vec2 TexCoordFinal;
in vec4 CurrentPositionFromLightPerspectiveNDC;

layout (binding = 5) uniform sampler2D sceneDepthMap;

//lighting/material related
//PBR
layout (binding = 0) uniform sampler2D albedoMap;
layout (binding = 1) uniform sampler2D roughnessMap;
layout (binding = 2)uniform sampler2D normalMap;
layout (binding = 3) uniform sampler2D aoMap;
layout (binding = 4) uniform sampler2D metallicMap;

in vec3 normals;
in vec3 WorldPos;

const float shadowMapBias = 0.0001;
const float PI = 3.14159;

//approximates microfacets.
float NDFGGX(vec3 normalVector, vec3 halfwayVector, float roughness)
{
	float roughnessSquared = roughness * roughness;

	float NDotH = max(dot(halfwayVector, normalVector),0.0);
	float NDotHSquared = NDotH * NDotH;
	
	float term = (NDotHSquared * (roughnessSquared - 1.0) + 1.0);
	float denominator = PI * term * term;
	
	return roughnessSquared/denominator;
}

//approximates light occlusion due to shadows.
float SelfShadowingGeometry(vec3 normalVector, vec3 vectorDirection,float roughness)
{
	float k = pow((roughness + 1) , 2) / 8.0;
	float NDotV = max(dot(normalVector, vectorDirection),0);
	return NDotV / (NDotV * (1 - k) + k );
}

float GeometrySmith(vec3 normalVector, vec3 viewVector, vec3 lightDirectionVector, float roughness)
{
	float ggx_one = SelfShadowingGeometry(normalVector,viewVector,roughness);
	float ggx_two = SelfShadowingGeometry(normalVector, lightDirectionVector, roughness);
	return ggx_one * ggx_two;
}

vec3 FresnelShlick(vec3 viewVector, vec3 halfwayVector, vec3 F0)
{
	float cosTheta = max( dot(viewVector,halfwayVector) ,0);
	return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}


vec3 computePBRLight(vec3 lightColor, vec3 normalVector,vec3 viewVector, vec3 lightDirectionVector, 
float roughness, vec3 F0, float metallic, vec3 albedo)
{
	vec3 radiance = lightColor;

	vec3 halfwayVector = normalize(lightDirectionVector + viewVector);

	float N = NDFGGX(normalVector, halfwayVector, roughness);
	float G = GeometrySmith(normalVector,viewVector,lightDirectionVector,roughness);
	vec3 F = FresnelShlick(viewVector,halfwayVector,F0);
	
	float NDotL = max(dot(normalVector,lightDirectionVector) , 0);
	float NDotV = max(dot(normalVector,viewVector) , 0);
	
	vec3 Specular =  (N * G * F) / (4.0 * (NDotL* NDotV) + 0.0001);

	vec3 kS = F;

	vec3 kD = vec3(1.0) - kS;
	
	//prevent difuse lighting if material is metallic.
	kD *= (1.0 - metallic);
	
	vec3 Lo = ( ((kD * albedo / 3.14159)) + Specular ) * radiance * NDotL;

	return Lo;
}

float ComputePCF(vec3 currentPosition, float bias, float currentDepth)
{
	float shadow = 0.0;
	vec2 texelSizePerPixel = 1.0 / textureSize(sceneDepthMap,0);
	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <=1; ++x)
		{
			float closestDepth = texture(sceneDepthMap, currentPosition.xy + vec2(x,y) * texelSizePerPixel ).r;
			if (currentDepth - bias > closestDepth)
			{
			shadow += 1.0;
			}
			else
			{
			shadow += 0.0;
			}
		}
	}

	shadow /= 9.0;
	return shadow;
}

float ShadowCalculation(vec3 currentPosition,float bias)
{
	if (currentPosition.z > 1.0)
	{
		return 0.0;
	}

	float currentDepth = currentPosition.z;
	//float closestDepth = ComputePCF(currentPosition, bias, currentDepth);
	float closestDepth  = texture(sceneDepthMap, currentPosition.xy).r;
	if (closestDepth + bias < currentDepth)
	{
		return 0.6;
	}

	return 0.0;
}

vec3 getNormalFromMap(vec2 aTexCoordFinal)
{
    vec3 tangentNormal = texture(normalMap, aTexCoordFinal).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(aTexCoordFinal);
    vec2 st2 = dFdy(aTexCoordFinal);

    vec3 N   = normalize(normals);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

void main()
{
	//normalize from 0 to 1
	vec3 CurrentPositionFromLightPerspectiveNormalized = CurrentPositionFromLightPerspectiveNDC.xyz / CurrentPositionFromLightPerspectiveNDC.w;
	CurrentPositionFromLightPerspectiveNormalized = CurrentPositionFromLightPerspectiveNormalized * 0.5 + 0.5;
	float bias = 0.00005;

	vec3 cameraPosition = vec3(0, 500 ,200);	//TODO UNIFORM UBFFER
	vec3 lightColor = vec3(1.0,1.0,1.0);
	vec3 lightDirection = vec3(0.0, 0.67, 0.99);

	float shadow = ShadowCalculation(CurrentPositionFromLightPerspectiveNormalized,bias);

	vec2 aTexCoordFinal = TexCoordFinal * 20;
	float m_height = height / 64.0f;

	vec3 F0 = vec3(0.01);
	vec3 albedo = pow( texture(albedoMap, aTexCoordFinal).rgb ,vec3(2.2));
	float metallic = texture(metallicMap, aTexCoordFinal).r;
	float ao = texture(aoMap, aTexCoordFinal).r;
	float roughness = texture(roughnessMap, aTexCoordFinal).r;
	F0 = mix(F0, albedo, metallic);

	vec3 lightColorFinal = computePBRLight(
	lightColor,
	getNormalFromMap(aTexCoordFinal),
	normalize(cameraPosition - WorldPos),
	lightDirection, 
	roughness,
	F0,
	metallic,
	albedo
	);

	
	vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 finalColor = ambient + lightColorFinal;
	
	finalColor = finalColor / (finalColor + vec3(1.0));
	finalColor = pow(finalColor, vec3(1.0/2.2)); 
	finalColor *= (1.0 - shadow);
	fragColor = vec4(finalColor, 1.0);
}

