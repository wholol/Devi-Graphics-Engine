#include "PhongMaterial.h"
#include "BindingLocation.h"

namespace Devi
{
	PhongMaterial::PhongMaterial(const std::string& name, std::shared_ptr<ITexture> albedoMap)
		:Material(name,albedoMap)
	{
	}

	PhongMaterial::PhongMaterial(const std::string & name, glm::vec4 albedo)
		: Material(name, albedo)
	{
	}

	void PhongMaterial::SetMaterialUniforms(std::shared_ptr<Shader> shader)
	{
		if (m_type == MaterialType::Textured)
		{
			shader->SetUniform(m_albedoMap->GetName(), DEVI_UNIFORM_ALBEDOMAP, UniformDataType::UNSIGNEDINT);
		}
		else
		{
			shader->SetUniform("albedo", m_albedo, UniformDataType::FLOAT);
		}

		if (m_normalMap)
		{
			shader->SetUniform(m_normalMap->GetName(), DEVI_UNIFORM_NORMALMAP, UniformDataType::UNSIGNEDINT);
		}

		if (m_specularMap)
		{
			shader->SetUniform(m_specularMap->GetName(), DEVI_UNIFORM_SPECULARMAP, UniformDataType::UNSIGNEDINT);
		}
		else
		{
			shader->SetUniform("specularShininess", m_specularShininess, UniformDataType::FLOAT);
		}
	}

	void PhongMaterial::Bind(std::shared_ptr<Shader> shader)
	{
		if (m_type == MaterialType::Textured)
		{
			m_albedoMap->Bind(DEVI_UNIFORM_ALBEDOMAP);
		}
		else
		{
			shader->SetUniform("albedo", m_albedo, UniformDataType::VEC4);
		}
		
		if (m_specularMap)
		{
			m_specularMap->Bind(DEVI_UNIFORM_SPECULARMAP);
		}
		else
		{
			shader->SetUniform("specularShininess", m_specularShininess, UniformDataType::FLOAT);
		}

		if (m_normalMap)
		{
			m_normalMap->Bind(DEVI_UNIFORM_NORMALMAP);
		}
	}
}

