#pragma once
#include "MaterialInstance.h"
#include "Material.h"
#include "../src/BindingLocation.h"

namespace Devi
{
	//probalby template this class.
	class PBRMaterialInstance : public MaterialInstance
	{
	public:
		PBRMaterialInstance(const std::string& name,std::shared_ptr<Material> material);
		
		// textured PBR
		void SetRoughness(std::shared_ptr<ITexture> roughnessMap);
		void SetMetallic(std::shared_ptr<ITexture> metallicMap);
		void SetAo(std::shared_ptr<ITexture> aoMap);
	
		// untextured PBR
		void SetRoughness(float roughness);
		void SetMetallic(float metallic);
		void SetAo(float ao);

		void Bind(std::shared_ptr<Shader> shader) override;


	private:

		//TODO templatize
		std::shared_ptr<ITexture> m_roughnessMap;
		std::shared_ptr<ITexture> m_metallicMap;
		std::shared_ptr<ITexture> m_aoMap;

		float m_roughness;
		float m_metallic;
		float m_ao;
	};
}