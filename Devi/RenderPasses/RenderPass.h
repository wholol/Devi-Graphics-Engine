#pragma once
#include "../src/Shader.h"
#include "../src/ITexture.h"
#include <vector>
#include "../src/FrameBuffer.h"
#include "../src/IDrawable.h"
#include "../Materials/Material.h"
#include <unordered_map>
#include <functional>

namespace Devi
{
	class Drawable;

	enum class RenderPassType
	{
		Default,
		ShadowMap,
		Water,
	};

	struct RenderPassObject
	{
		std::shared_ptr<Shader> shader = nullptr;
		std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures;
		Drawable* drawable = nullptr;
		std::shared_ptr<Material> material;
	};

	struct Step
	{
		std::vector<RenderPassObject> renderQueue;
	};

	class RenderPass
	{

	public:	
		void Submit(std::shared_ptr<Shader> shader, const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures,
			std::shared_ptr<Material> material,
			Drawable* drawable, unsigned int stepNumber = 0);

		//input/dependency from another pass.
		void LinkRenderPass(std::shared_ptr<RenderPass> renderpass);
		
		//get outputs (rendertarget) for this renderpass
		std::shared_ptr<FrameBuffer> GetFrameBuffer(const std::string& name) const;

		void SetRenderPassType(RenderPassType renderPassType);

		template <typename T>
		void SortCriteria(std::function<T> sortCriteria, unsigned int stepNumber);

		template<typename T>
		inline void RenderPass::SortCriteria(std::function<T> sortCriteria, unsigned int stepNumber)
		{
			if (!m_isStepsSorted)
			{
				SortSteps();
			}

			std::sort(m_steps[stepNumber].renderQueue.begin(), m_steps[stepNumber].renderQueue.end(), sortCriteria);
		}

		const Step& GetStep(unsigned int stepNumber) const;

		RenderPassType GetRenderPassType() const;

		virtual void Execute() = 0;

	protected:
		std::unordered_map<unsigned int, Step> m_stepMap;

		bool m_isStepsSorted = false;
		
		std::unordered_map<RenderPassType,std::shared_ptr<RenderPass>> m_dependencyRenderPasses;
		std::unordered_map<std::string, std::shared_ptr<FrameBuffer>> m_frameBufferMap;

		RenderPassType m_renderPassType;
	};
	

}