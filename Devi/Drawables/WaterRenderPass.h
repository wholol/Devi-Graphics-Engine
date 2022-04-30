#pragma once
#include "../src/FrameBuffer.h"
#include "../src/IDrawable.h"
#include <vector>

namespace Devi
{
	class WaterRenderPass
	{
		public:
			WaterRenderPass(int textureWidth, int textureHeight, const std::vector<DrawablePtr>& drawables);
			void execute();
		private:
			int m_textureWidth;
			int m_textureHeight;
			std::shared_ptr<Texture2D> m_reflectionTexture;
			std::shared_ptr<Texture2D> m_refractionTexture;
			FrameBuffer m_waterReflectionFrameBuffer;
			FrameBuffer m_waterRefractionFrameBuffer;
			const std::vector<DrawablePtr>& m_drawables;
	};
}
