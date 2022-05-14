#include "Light.h"

namespace Devi
{
	Light::Light(glm::vec3 lightColor)
		:m_LightColor(lightColor)
	{}

	glm::vec3 Light::GetLightColor() const
	{
		return m_LightColor;
	}

	LightType Light::GetLightType() const
	{
		return m_lightType;
	}
}

