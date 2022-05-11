#pragma once
#include <string>
#include "Material.h"

namespace Devi
{
	class MaterialInstance
	{
	public:
		MaterialInstance(const std::string& name, std::shared_ptr<Material> material);
		void SetNormalMap(std::shared_ptr<ITexture> normalMap);
		std::string GetName() const;
		virtual void Bind(std::shared_ptr<Shader> shader) = 0;

	protected:
		std::string m_name;
		
		std::shared_ptr<Material> m_material;
		std::shared_ptr<ITexture> m_normalMap;

		bool m_textureUniformsSet = false;
		bool m_hasNormalMap = false;
	};

}