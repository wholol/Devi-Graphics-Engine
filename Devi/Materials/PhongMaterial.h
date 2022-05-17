#pragma once
#include "../Materials/Material.h"

namespace Devi
{
	class PhongMaterial : public Material
	{
		
	public:
		
		PhongMaterial(const std::string& name, std::shared_ptr<ITexture> albedoMap);
		PhongMaterial(const std::string& name, glm::vec4 albedo);

		void SetSpecular(float specularshininess);
		void SetSpecular(std::shared_ptr<ITexture> specularMap);
		
		void SetMaterialUniforms(std::shared_ptr<Shader> shader) override;
		void Bind(std::shared_ptr<Shader> shader) override;
		
	private:
		float m_specularShininess;
		std::shared_ptr<ITexture> m_specularMap;

	};
}
