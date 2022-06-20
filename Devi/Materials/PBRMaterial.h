#pragma once
#include "Material.h"

namespace Devi
{
	class PBRMaterial : public Material
	{
	public:
		PBRMaterial(const std::string& name, std::shared_ptr<ITexture> albedoMap);
		PBRMaterial(const std::string& name, glm::vec4 albedo);

		// textured PBR
		void SetRoughness(std::shared_ptr<ITexture> roughnessMap);
		void SetMetallic(std::shared_ptr<ITexture> metallicMap);
		void SetAo(std::shared_ptr<ITexture> aoMap);

		// untextured PBR
		void SetRoughness(float roughness);
		void SetMetallic(float metallic);
		void SetAo(float ao);

		void SetMaterialUniforms(std::shared_ptr<Shader> shader) override;
		void Bind(std::shared_ptr<Shader> shader) override;

	private:
		//TODO templatize these.
		std::shared_ptr<ITexture> m_roughnessMap;
		std::shared_ptr<ITexture> m_metallicMap;
		std::shared_ptr<ITexture> m_aoMap;

		float m_roughness;
		float m_metallic;
		float m_ao;
	};

}