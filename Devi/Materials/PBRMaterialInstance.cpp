#include "PBRMaterialInstance.h"

namespace Devi
{
	PBRMaterialInstance::PBRMaterialInstance(const std::string& name, std::shared_ptr<Material> material)
		:MaterialInstance(name,material)
	{
	}
	void PBRMaterialInstance::SetRoughness(std::shared_ptr<ITexture> roughnessMap)
	{
		m_roughnessMap = roughnessMap;
	}

	void PBRMaterialInstance::SetMetallic(std::shared_ptr<ITexture> metallicMap)
	{
		m_metallicMap = metallicMap;
	}

	void PBRMaterialInstance::SetAo(std::shared_ptr<ITexture> aoMap)
	{
		m_aoMap = aoMap;
	}

	void PBRMaterialInstance::SetRoughness(float roughness)
	{
		m_roughness = roughness;
	}

	void PBRMaterialInstance::SetMetallic(float metallic)
	{
		m_metallic = metallic;
	}

	void PBRMaterialInstance::SetAo(float ao)
	{
		m_ao = ao;
	}

	void PBRMaterialInstance::Bind(std::shared_ptr<Shader> shader)
	{
		if (!m_textureUniformsSet)
		{
			if (m_hasNormalMap)
			{
				shader->SetUniform("normalMap", DEVI_UNIFORM_NORMALMAP, UniformDataType::UNSIGNEDINT);
			}
			shader->SetUniform("albedoMap", DEVI_UNIFORM_ALBEDOMAP, UniformDataType::UNSIGNEDINT);
			shader->SetUniform("roughnessMap", DEVI_UNIFORM_ROUGHNESSMAP, UniformDataType::UNSIGNEDINT);
			shader->SetUniform("metallicMap", DEVI_UNIFORM_METALLICMAP, UniformDataType::UNSIGNEDINT);
			shader->SetUniform("aoMap", DEVI_UNIFORM_AOMAP, UniformDataType::UNSIGNEDINT);

			m_textureUniformsSet = true;
		}

		m_material->Bind(shader);
		m_aoMap->Bind(DEVI_UNIFORM_AOMAP);
		m_metallicMap->Bind(DEVI_UNIFORM_METALLICMAP);
		m_roughnessMap->Bind(DEVI_UNIFORM_ROUGHNESSMAP);

		shader->SetUniform("ao", m_ao, UniformDataType::FLOAT);
		shader->SetUniform("metallic", m_metallic, UniformDataType::FLOAT);
		shader->SetUniform("roughness", m_roughness, UniformDataType::FLOAT);
	}
}

