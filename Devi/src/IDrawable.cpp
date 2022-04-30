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

	void Drawable::SubmitToRenderPass(std::shared_ptr<RenderPassManager> renderPassManager, RenderPassType type, std::shared_ptr<Shader> shader,std::optional<std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>> textures)
	{
		if( !textures.has_value() )	//e.g. shadow mapping does not need textures.
		{
			std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> noTextureAtAll;
			noTextureAtAll.reserve(0);

			renderPassManager->SubmitRenderPassOperation(type, shader, noTextureAtAll, this);
		}
		else
		{
			renderPassManager->SubmitRenderPassOperation(type, shader, textures.value(), this);
		}
	}
}

