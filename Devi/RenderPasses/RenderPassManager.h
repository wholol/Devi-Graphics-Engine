#pragma once
#include "RenderPass.h"
#include <unordered_map>
#include "../Materials/MaterialInstance.h"


namespace Devi
{
	class RenderPass;
	class Drawable;
	enum class RenderPassType;

	class RenderPassManager
	{
	public:
		void Init();
		void AddRenderPass(std::shared_ptr<RenderPass> renderPass, RenderPassType renderPassType);
		std::shared_ptr<RenderPass> GetRenderPass(RenderPassType renderPassType);

		void SubmitRenderPassOperation(RenderPassType type, std::shared_ptr<Shader> shader, 
			const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures, 
			std::shared_ptr<MaterialInstance> materialInstance,
			Drawable* drawable);
		
		void ExecutePasses();

	private:
		std::unordered_map<RenderPassType, std::shared_ptr<RenderPass>> m_renderPassMap;
	};
};