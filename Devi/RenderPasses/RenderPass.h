#pragma once
#include "../src/Shader.h"
#include "../src/ITexture.h"
#include <vector>
#include "../src/FrameBuffer.h"
#include "../src/IDrawable.h"
#include "../Materials/MaterialInstance.h"

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
		std::shared_ptr<MaterialInstance> m_materialInstance;
	};

	class RenderPass
	{
	public:

		void Submit(std::shared_ptr<Shader> shader, const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures, Drawable* drawable);

		virtual void Execute() = 0;

		void ClearRenderQueue();

	protected:
		std::vector<RenderPassObject> m_renderQueue;
	};
}