#version 460 core

in float height;
out vec4 fragColor;

in vec2 TexCoordFinal;
in vec4 CurrentPositionFromLightPerspectiveNDC;
in vec3 normals;

layout (binding = 1) uniform sampler2D grass;
layout (binding = 5) uniform sampler2D sceneDepthMap;

float ComputePCF(vec3 currentPosition, float bias, float currentDepth)
{
	float shadow = 0.0;
	vec2 texelSizePerPixel = 1.0 / textureSize(sceneDepthMap,0);
	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <=1; ++x)
		{
			float closestDepth = texture(sceneDepthMap, currentPosition.xy + vec2(x,y) * texelSizePerPixel ).r;
			if (closestDepth + bias  < currentDepth) {shadow += 1.0;}
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

//PBR
//uniform sampler2D albedoMap;
//uniform sampler2D roughnessMap;
//uniform sampler2D normalMap;
//uniform sampler2D aoMap;
//uniform sampler2D metallicMap;

void main()
{
	//normalize from 0 to 1
	vec3 CurrentPositionFromLightPerspectiveNormalized = CurrentPositionFromLightPerspectiveNDC.xyz / CurrentPositionFromLightPerspectiveNDC.w;
	CurrentPositionFromLightPerspectiveNormalized = CurrentPositionFromLightPerspectiveNormalized * 0.5 + 0.5;
	float bias = 0.0005;

	float shadow = ShadowCalculation(CurrentPositionFromLightPerspectiveNormalized,bias);

	vec2 aTexCoordFinal = TexCoordFinal * 20;
	float m_height = height / 64.0f;

	vec3 landColor = texture(grass, aTexCoordFinal).rgb;

	landColor *= (1.0 - shadow);

	fragColor = vec4(landColor, 1.0);
}


////approximates microfacets.
//float NDFGGX(vec3 normalVector, vec3 halfwayVector, float roughness)
//{
//	float roughnessSquared = roughness * roughness;
//	float term = max(dot(halfwayVector, normalVector),0) * max(dot(halfwayVector, normalVector),0) * (roughnessSquared - 1) + 1 ;
//	float denominator = 3.41459 * term * term;
//
//	return roughnessSquared/denominator;
//}
//
////approximates light occlusion due to shadows.
//float SelfShadowingGeometry(vec3 normalVector, vec3 vectorDirection,float roughness)
//{
//	float k = pow((roughness + 1) , 2) / 8.0;
//	float NDotV = max(dot(normalVector, vectorDirection),0);
//	return NDotV / (NDotV * (1 - k) + k );
//}
//
//float GeometrySmith(vec3 normalVector, vec3 viewVector, vec3 lightDirectionVector, float roughness)
//{
//	float ggx_one = SelfShadowingGeometry(normalVector,viewVector,roughness);
//	float ggx_two = SelfShadowingGeometry(normalVector, lightDirectionVector, roughness);
//	return ggx_one * ggx_two;
//}
//
//vec3 FresnelShlick(vec3 viewVector, vec3 halfwayVector, vec3 F0)
//{
//	float cosTheta = max( dot(viewVector,halfwayVector) ,0);
//	return F0 + (1.0 - F0) * pow ((1.0 -  cosTheta),5);
//}
//
//
//vec3 computePBRLight(vec3 lightColor, vec3 normalVector,vec3 viewVector, vec3 lightDirectionVector, 
//float roughness, vec3 F0, float metallic, float ao)
//{
//	vec3 radiance = lightColor;
//
//	vec3 halfwayVector = lightDirectionVector + viewVector;
//
//	float N = NDFGGX(normalVector, halfwayVector, roughness);
//	float G = GeometrySmith(normalVector,viewVector,lightDirectionVector,roughness);
//	vec3 F = FresnelShlick(viewVector,halfwayVector,F0);
//
//	float NDotL = max(dot(normalVector,lightDirectionVector) , 0);
//	float NDotV = max(dot(normalVector,viewVector) , 0);
//
//	vec3 kS =  (N * G * F) / (4.0 * (NDotL* NDotV)) + 0.0001;
//
//	vec3 kD = (vec3(1.0) - F) * (1.0 - metallic);
//
//	vec3 Lo = (((kD * lightColor) / 3.14159) + kS) * radiance * NDotL;
//
//	return Lo;
//}

