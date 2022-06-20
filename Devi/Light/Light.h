#pragma once
#include <../Dependencies/Math/glm/glm.hpp>

namespace Devi
{
	enum class LightType
	{
		DirectionalLight,
		PointLight
	};

	class Light
	{
	public:
		Light(glm::vec3 lightColor);
		glm::vec3 GetLightColor() const;
		LightType GetLightType() const;

	protected:
		glm::vec3 m_LightColor;
		LightType m_lightType;
	};
}
