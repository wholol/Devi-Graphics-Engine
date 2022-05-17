#version 460 core

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