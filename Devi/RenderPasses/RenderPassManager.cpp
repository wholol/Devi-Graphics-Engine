#include "RenderPassManager.h"
#include "ShadowMapRenderPass.h"

namespace Devi
{
	void RenderPassManager::Init()
	{
		int shadowMapScreenWidth = 800;
		int shadowMapScreenHeight = 800;

		ShadowMapMatrixParams newparams;
		newparams.top = 1000.0f;
		newparams.bottom = -1000.0f;
		newparams.left = -1000.0f;
		newparams.right = 1000.0f;
		newparams.zNear = -1000.0f;
		newparams.zFar = 1000.0f;

		AddRenderPass(
			std::make_shared<ShadowMapRenderPass>(shadowMapScreenWidth, shadowMapScreenHeight, newparams),
			RenderPassType::ShadowMap
		);
	}
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

		return nullptr;
	}

	void RenderPassManager::SubmitRenderPassOperation(RenderPassType renderPassType, std::shared_ptr<Shader> shader,const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures, Drawable* drawable)
	{
		auto findPass = m_renderPassMap.find(renderPassType);

		if (findPass != m_renderPassMap.end())
		{
			auto pass = findPass->second;

			pass->Submit(shader, textures, drawable);
		}
	}

	void RenderPassManager::ExecutePasses()
	{
		GetRenderPass(RenderPassType::ShadowMap)->Execute();
	}
}



