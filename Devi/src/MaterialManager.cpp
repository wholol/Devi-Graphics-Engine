#include "MaterialManager.h"

namespace Devi
{
	void MaterialManager::AddMaterial(std::shared_ptr<Material> material)
	{
		auto name = material->GetName();
		auto findMaterialName = m_materialMap.find(name);

		if (findMaterialName != m_materialMap.end())
		{
			DEVI_ERROR("The material: " + material->GetName() + " is not loaded. The name already exists.", __FILE__, __LINE__);
		}
		else
		{
			m_materialMap.insert({ name, material });
		}
	}

	std::shared_ptr<Material> MaterialManager::GetMaterial(const std::string& name)
	{
		auto findMaterial = m_materialMap.find(name);

		if (findMaterial != m_materialMap.end())
		{
			return findMaterial->second;
		}
		else
		{
			DEVI_ERROR("The material: " + name + " cannot be found.", __FILE__, __LINE__);
		}

		return nullptr;
	}
}

