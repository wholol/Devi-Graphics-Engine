#pragma once
#include <unordered_map>
#include "../Materials/Material.h"

namespace Devi
{
	class MaterialManager
	{
	public:
		void AddMaterial(std::shared_ptr<Material> material);
		std::shared_ptr<Material> GetMaterial(const std::string& name);

	private:
		std::unordered_map<std::string, std::shared_ptr<Material>> m_materialMap;
	};
}