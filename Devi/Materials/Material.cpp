#include "Material.h"
#include "../src/BindingLocation.h"

namespace Devi
{
	Material::Material(const std::string& name, std::shared_ptr<ITexture> albedoMap)
		:m_name(name),
		m_albedoMap(albedoMap),
		m_type(MaterialType::Textured)
	{
	}

	Material::Material(const std::string & name, glm::vec4 albedo)
		:m_name(name),
		m_albedo(albedo),
		m_type(MaterialType::CustomRGBA)
	{}

	void Material::SetNormalMap(std::shared_ptr<ITexture> normalMap)
	{
		m_normalMap = normalMap;
	}

	std::string Material::GetName() const
	{
		return m_name;
	}

	MaterialType Material::GetType() const
	{
		return m_type;
	}

	void Material::Bind(std::shared_ptr<Shader> shader)
	{
		if (m_type == MaterialType::Textured)
		{
			m_albedoMap->Bind(DEVI_UNIFORM_ALBEDOMAP);
		}
		else
		{
			shader->SetUniform("albedo", m_albedo, UniformDataType::VEC4);
		}
	}
}

