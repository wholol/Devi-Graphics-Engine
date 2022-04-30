#pragma once
#include "Shader.h"
#include "ITexture.h"
#include <vector>
#include "FrameBuffer.h"
#include "IDrawable.h"

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
		Drawable* drawable = nullptr;	//DRAWABLEPTR NOT USED DUE TO CIRCULAR DEPENDENCY
	};

	class RenderPass
	{
	public:

		void Submit(std::shared_ptr<Shader> shader, const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures, Drawable* drawable)
		{
			RenderPassObject renderPassObject;

			renderPassObject.shader = shader;
			renderPassObject.textures = std::move(textures);
			renderPassObject.drawable = drawable;

			m_renderQueue.emplace_back(renderPassObject);
		};

		virtual void Execute() = 0;

		void clearRenderQueue()
		{
			m_renderQueue.clear();
		}

	protected:
		std::vector<RenderPassObject> m_renderQueue;
	};
}