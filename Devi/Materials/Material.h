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

		void SetNormalMap(std::shared_ptr<ITexture> normalMap);
		
		virtual void SetMaterialUniforms(std::shared_ptr<Shader> shader) = 0;

		virtual void Bind(std::shared_ptr<Shader> shader) = 0;

		std::string GetName() const;
		
		MaterialType GetType() const;

	protected:
		
		std::string m_name;
		//TODO templates?
		glm::vec4 m_albedo;
		std::shared_ptr<ITexture> m_albedoMap;	

		std::shared_ptr<ITexture> m_normalMap;
		bool m_hasNormalMap = false;

		MaterialType m_type;
		
	};
}
