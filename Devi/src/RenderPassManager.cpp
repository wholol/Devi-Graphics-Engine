#include "RenderPassManager.h"

namespace Devi
{
	void RenderPassManager::AddRenderPass(std::shared_ptr<RenderPass> renderPass, RenderPassType renderPassType)
	{
		m_renderPassMap.insert(std::make_pair(renderPassType, renderPass));
	}

	std::shared_ptr<RenderPass> RenderPassManager::GetRenderPass(RenderPassType renderPassType)
	{
		auto findPass = m_renderPassMap.find(renderPassType);

		if (findPass != m_renderPassMap.end())
		{
			return findPass->second;
		}
	}

	void RenderPassManager::SubmitRenderPassOperation(RenderPassType renderPassType, std::shared_ptr<Shader> shader, const std::vector<std::shared_ptr<ITexture>>& textures, DrawablePtr drawable)
	{
		auto findPass = m_renderPassMap.find(renderPassType);

		if (findPass != m_renderPassMap.end())
		{
			auto pass = findPass->second;

			pass->Submit(shader, textures, drawable);
		}
	}
}



