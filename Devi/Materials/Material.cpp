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
		m_albedo(m_albedo),
		m_type(MaterialType::CustomRGBA)
	{}

	std::string Material::GetName() const
	{
		return m_name;
	}

	glm::vec4 Material::GetAlbedoVec4() const
	{
		return m_albedo;
	}

	std::shared_ptr<ITexture> Material::GetAlbedoTexture() const
	{
		return m_albedoMap;
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
			shader->SetUniform("albedo", m_albedo, UniformDataType::FLOAT);
		}
	}
}

