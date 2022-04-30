#include "RenderPass.h"

namespace Devi
{

	void RenderPass::Submit(std::shared_ptr<Shader> shader, const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures, Drawable * drawable)
	{
		RenderPassObject renderPassObject;

		renderPassObject.shader = shader;
		renderPassObject.textures = std::move(textures);
		renderPassObject.drawable = drawable;

		m_renderQueue.emplace_back(renderPassObject);
	}

	void RenderPass::ClearRenderQueue()
	{
		m_renderQueue.clear();
	}

}