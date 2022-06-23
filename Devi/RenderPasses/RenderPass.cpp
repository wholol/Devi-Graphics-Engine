#include "RenderPass.h"
#include <algorithm>

namespace Devi
{
	void RenderPass::Submit(std::shared_ptr<Shader> shader, 
		const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures, 
		std::shared_ptr<Material> material, 
		Drawable* drawable, 
		unsigned int stepNumber)
	{
		RenderPassObject renderPassObject;

		renderPassObject.shader = shader;
		renderPassObject.textures = std::move(textures);
		renderPassObject.drawable = drawable;
		renderPassObject.material = material;

		auto findStep = m_stepMap.find(stepNumber);

		if (findStep != m_stepMap.end())
		{
			auto& q = findStep->second.renderQueue;
			q.emplace_back(renderPassObject);
		}
		else
		{
			Step step;
			step.renderQueue.emplace_back(renderPassObject);
			m_stepMap.insert(std::make_pair(stepNumber, step));
		}
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

	const Step& RenderPass::GetStep(unsigned int stepNumber) const
	{
		auto findStep = m_stepMap.find(stepNumber);

		if (findStep != m_stepMap.end())
		{
			return findStep->second;
		}
		else
		{
			DEVI_ERROR("Step number: " + std::to_string(stepNumber) + " not found for RenderPassType: TODO", __FILE__, __LINE__);
		}
	}

	RenderPassType RenderPass::GetRenderPassType() const
	{
		return m_renderPassType;
	}
}