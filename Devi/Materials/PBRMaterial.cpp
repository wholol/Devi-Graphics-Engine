#include "PBRMaterial.h"
#include "BindingLocation.h"

namespace Devi
{
	PBRMaterial::PBRMaterial(const std::string& name, std::shared_ptr<ITexture> albedoMap)
		:Material(name, albedoMap)
	{}

	PBRMaterial::PBRMaterial(const std::string & name, glm::vec4 albedo)
		:Material(name,albedo)
	{}

	void PBRMaterial::SetRoughness(std::shared_ptr<ITexture> roughnessMap)
	{
		m_roughnessMap = roughnessMap;
	}

	void PBRMaterial::SetMetallic(std::shared_ptr<ITexture> metallicMap)
	{
		m_metallicMap = metallicMap;
	}

	void PBRMaterial::SetAo(std::shared_ptr<ITexture> aoMap)
	{
		m_aoMap = aoMap;
	}

	void PBRMaterial::SetRoughness(float roughness)
	{
		m_roughness = roughness;
	}

	void PBRMaterial::SetMetallic(float metallic)
	{
		m_metallic = metallic;
	}

	void PBRMaterial::SetAo(float ao)
	{
		m_ao = ao;
	}

	void PBRMaterial::SetMaterialUniforms(std::shared_ptr<Shader> shader)
	{
		if (GetType() == MaterialType::Textured)
		{
			shader->SetUniform("albedoMap", DEVI_UNIFORM_ALBEDOMAP, UniformDataType::UNSIGNEDINT);
		}
		else
		{
			shader->SetUniform("albedo", m_albedo, UniformDataType::VEC4);
		}

		if (m_roughnessMap)
		{
			shader->SetUniform("roughnessMap", DEVI_UNIFORM_ROUGHNESSMAP, UniformDataType::UNSIGNEDINT);
		}
		else
		{
			shader->SetUniform("roughness", m_roughness, UniformDataType::FLOAT);
		}

		if (m_metallicMap)
		{
			shader->SetUniform("metallicMap", DEVI_UNIFORM_METALLICMAP, UniformDataType::UNSIGNEDINT);
		}
		else
		{
			shader->SetUniform("metallic", m_metallicMap, UniformDataType::FLOAT);
		}

		if (m_aoMap)
		{
			shader->SetUniform("aoMap", DEVI_UNIFORM_AOMAP, UniformDataType::UNSIGNEDINT);
		}
		else
		{
			shader->SetUniform("ao", m_ao, UniformDataType::FLOAT);
		}
		
		if (m_normalMap)
		{
			shader->SetUniform("normalMap", DEVI_UNIFORM_NORMALMAP, UniformDataType::UNSIGNEDINT);
		}
	}

	void PBRMaterial::Bind(std::shared_ptr<Shader> shader)
	{
		if (GetType() == MaterialType::Textured)
		{
			m_albedoMap->Bind(DEVI_UNIFORM_ALBEDOMAP);
		}
		else
		{
			shader->SetUniform("albedo", m_albedo, UniformDataType::FLOAT);
		}

		if (m_roughnessMap)
		{
			m_roughnessMap->Bind(DEVI_UNIFORM_ROUGHNESSMAP);
		}
		else
		{
			shader->SetUniform("roughness", m_roughness, UniformDataType::FLOAT);
		}

		if (m_metallicMap)
		{
			m_metallicMap->Bind(DEVI_UNIFORM_METALLICMAP);
		}
		else
		{
			shader->SetUniform("metallic", m_metallicMap, UniformDataType::FLOAT);
		}

		if (m_aoMap)
		{
			m_aoMap->Bind(DEVI_UNIFORM_AOMAP);
		}
		else
		{
			shader->SetUniform("ao", m_ao, UniformDataType::FLOAT);
		}

		if (m_normalMap)
		{
			m_normalMap->Bind(DEVI_UNIFORM_NORMALMAP);
		}
	}
}

