#pragma once
#include <string>
#include "MaterialInstance.h"
#include "Material.h"
#include "../src/ITexture.h"

namespace Devi
{
	//TODO probably templatize this (one typenmae for each param?)
	class PhongMaterialInstance : public MaterialInstance
	{
	public:
		
		PhongMaterialInstance(const std::string& name, std::shared_ptr<Material> material);
		void SetSpecular(float specularshininess);
		void SetSpecular(std::shared_ptr<ITexture> specularMap);
		void Bind(std::shared_ptr<Shader> shader) override;
	
	private:

		float m_specularShininess;
		std::shared_ptr<ITexture> m_specularMap;
	};
};