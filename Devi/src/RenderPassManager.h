#pragma once
#include "IDrawable.h"
#include "RenderPass.h"
#include <unordered_map>


namespace Devi
{
	class RenderPassManager
	{
	public:
		void AddRenderPass(std::shared_ptr<RenderPass> renderPass, RenderPassType renderPassType);
		std::shared_ptr<RenderPass> GetRenderPass(RenderPassType renderPassType);
		void SubmitRenderPassOperation(RenderPassType type, std::shared_ptr<Shader> shader, const std::vector<std::shared_ptr<ITexture>>& textures, DrawablePtr drawable);

	private:
		std::unordered_map<RenderPassType, std::shared_ptr<RenderPass>> m_renderPassMap;
	};
};