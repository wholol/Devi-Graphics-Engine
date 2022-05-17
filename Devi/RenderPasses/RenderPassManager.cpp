#include "RenderPassManager.h"
#include "ShadowMapRenderPass.h"
#include "DefaultRenderPass.h"

namespace Devi
{
	void RenderPassManager::Init()
	{
		int shadowMapScreenWidth = 800;
		int shadowMapScreenHeight = 800;

		ShadowMapOrthoMatrixParams newparams;
		newparams.top = 1000.0f;
		newparams.bottom = -1000.0f;
		newparams.left = -1000.0f;
		newparams.right = 1000.0f;
		newparams.right = 1000.0f;
		newparams.zNear = -1000.0f;
		newparams.zFar = 1000.0f;

		//shadow map pass
		auto shadowMapRenderPass = std::make_shared<ShadowMapRenderPass>(shadowMapScreenWidth, shadowMapScreenHeight, newparams, 
			std::make_shared<DirectionalLight>(glm::vec3(0.0, -0.67, -0.99), glm::vec3(0.0f, 800.0f, 0.0f)));
		
		AddRenderPass(shadowMapRenderPass, RenderPassType::ShadowMap);

		//normal pass
		auto normalPass = std::make_shared<DefaultRenderPass>();
		normalPass->LinkRenderPass(shadowMapRenderPass);

		AddRenderPass(normalPass, RenderPassType::Default);
			
	}
	void RenderPassManager::AddRenderPass(std::shared_ptr<RenderPass> renderPass, RenderPassType renderPassType)
	{
		renderPass->SetRenderPassType(renderPassType);
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

	void RenderPassManager::SubmitRenderPassOperation(RenderPassType renderPassType, std::shared_ptr<Shader> shader,
		const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures,
		std::shared_ptr<Material> material,
		Drawable* drawable)
	{
		auto findPass = m_renderPassMap.find(renderPassType);

		if (findPass != m_renderPassMap.end())
		{
			auto pass = findPass->second;

			pass->Submit(shader, textures, material, drawable);
		}
	}

	void RenderPassManager::ExecutePasses()
	{
		GetRenderPass(RenderPassType::ShadowMap)->Execute();

		GetRenderPass(RenderPassType::Default)->Execute();
	}
}



