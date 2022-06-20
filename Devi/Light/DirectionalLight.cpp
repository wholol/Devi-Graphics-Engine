#include "DirectionalLight.h"

namespace Devi
{
	DirectionalLight::DirectionalLight(glm::vec3 lightDirection, glm::vec3 lightPosition, glm::vec3 lightColor)
		:Light(lightColor),
		m_lightDirection(lightDirection),
		m_lightPosition(lightPosition)
	{
		m_lightType = LightType::DirectionalLight;
	}

	glm::vec3 DirectionalLight::GetLightDirection() const
	{
		return m_lightDirection;
	}

	glm::vec3 DirectionalLight::GetLightPosition() const
	{
		return m_lightPosition;
	}
}

