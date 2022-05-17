#include "RenderPass.h"

namespace Devi
{

	void RenderPass::Submit(std::shared_ptr<Shader> shader,
		const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures,
		std::shared_ptr<Material> material,
		Drawable* drawable)
	{
		RenderPassObject renderPassObject;

		renderPassObject.shader = shader;
		renderPassObject.textures = std::move(textures);
		renderPassObject.drawable = drawable;
		renderPassObject.material = material;

		m_renderQueue.emplace_back(renderPassObject);
	}

	void RenderPass::LinkRenderPass(std::shared_ptr<RenderPass> renderpass)
	{
		m_dependencyRenderPasses.insert(std::make_pair(renderpass->GetRenderPassType(), renderpass));
	}

	std::shared_ptr<FrameBuffer> RenderPass::GetFrameBuffer(const std::string& name) const
	{
		auto findFrameBuffer = m_frameBufferMap.find(name);

		if (findFrameBuffer != m_frameBufferMap.end())
		{
			return findFrameBuffer->second;
		}
		else
		{
			DEVI_ERROR("FrameBuffer for: " + name + " not found.", __FILE__, __LINE__);
		}

		return nullptr;
	}

	void RenderPass::SetRenderPassType(RenderPassType renderPassType)
	{
		m_renderPassType = renderPassType;
	}

	RenderPassType RenderPass::GetRenderPassType() const
	{
		return m_renderPassType;
	}
}