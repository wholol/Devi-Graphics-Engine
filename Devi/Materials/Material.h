#pragma once
#include <memory>
#include <string>
#include "../src/Shader.h"
#include "../src/ITexture.h"
#include "../Dependencies/Math/glm/glm.hpp"

namespace Devi
{
	enum class MaterialType
	{
		Textured,
		CustomRGBA
	};

	/**
	* Material class.Class for a base material for the drawable object.
	* TODO: Use templates
	*/
	class Material
	{
	public:
		Material(const std::string& name, std::shared_ptr<ITexture> albedoMap);
		Material(const std::string& name, glm::vec4 albedo);
		std::string GetName() const;
		glm::vec4 GetAlbedoVec4() const;
		std::shared_ptr<ITexture> GetAlbedoTexture() const;
		MaterialType GetType() const;
		void Bind(std::shared_ptr<Shader> shader);

	protected:
		std::string m_name;
		
		glm::vec4 m_albedo;
		std::shared_ptr<ITexture> m_albedoMap;	
		MaterialType m_type;
		
	};
}
