#include "PhongMaterialInstance.h"
#include "BindingLocation.h"

namespace Devi
{

	PhongMaterialInstance::PhongMaterialInstance(const std::string& name, std::shared_ptr<Material> material)
		:MaterialInstance(name, material)
	{
	}

	void PhongMaterialInstance::SetSpecular(float specularshininess)
	{
		m_specularShininess = specularshininess;
		
	}

	void PhongMaterialInstance::SetSpecular(std::shared_ptr<ITexture> specularMap)
	{
		m_specularMap = specularMap;
	}

	void PhongMaterialInstance::Bind(std::shared_ptr<Shader> shader)
	{

		if (!m_textureUniformsSet)
		{
			if (m_hasNormalMap)
			{
				shader->SetUniform("normalMap", DEVI_UNIFORM_NORMALMAP, UniformDataType::UNSIGNEDINT);
			}

			shader->SetUniform("specularMap", DEVI_UNIFORM_SPECULARMAP, UniformDataType::UNSIGNEDINT);
			m_textureUniformsSet = true;
		}

		m_material->Bind(shader);
		shader->SetUniform("specularShininess", m_specularShininess, UniformDataType::FLOAT);

	}
}

