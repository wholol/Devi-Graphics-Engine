#include "IDrawable.h"

namespace Devi
{
	Drawable::Drawable(const std::string & name)
		:m_name(name)
	{
	}

	std::string Drawable::GetName() const
	{
		return m_name;
	}

	void Drawable::SubmitToRenderPass(
		std::shared_ptr<RenderPassManager> renderPassManager, 
		unsigned int stepNumber,
		RenderPassType type, std::shared_ptr<Shader> shader,
		std::optional<std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>> textures,
		std::optional<std::shared_ptr<Material>> material)
	{
		std::shared_ptr<Material> materialInst = nullptr;

		if (material.has_value())
		{
			materialInst = material.value();
			materialInst->SetMaterialUniforms(shader);
		}

		if( !textures.has_value() )	//e.g. shadow mapping does not need textures.
		{
			std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> noTextureAtAll;
			noTextureAtAll.reserve(0);

			renderPassManager->SubmitRenderPassOperation(type, shader, noTextureAtAll, materialInst, this, stepNumber);
		}
		else
		{
			for (auto& texture : textures.value())
			{
				auto Texture = texture.first;

				shader->SetUniform(Texture->GetName(), texture.second, UniformDataType::UNSIGNEDINT);
			}

			renderPassManager->SubmitRenderPassOperation(type, shader, textures.value(), materialInst, this, stepNumber);
		}
	}
	const glm::mat4& Drawable::GetModelMatrix() const
	{
		return m_modelMatrix;
	}
}

