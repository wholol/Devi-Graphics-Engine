#include "MaterialInstance.h"
#include "../src/BindingLocation.h"

namespace Devi
{
	MaterialInstance::MaterialInstance(const std::string & name, std::shared_ptr<Material> material)
		:m_name(name),
		m_material(material)
	{
	}

	void MaterialInstance::SetNormalMap(std::shared_ptr<ITexture> normalMap)
	{
		m_normalMap = normalMap;
		m_hasNormalMap = true;
	}

	std::string MaterialInstance::GetName() const
	{
		return m_name;
	}
}

