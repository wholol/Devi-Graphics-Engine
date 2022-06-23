#pragma once
#include "RenderPass.h"
#include "FrameBuffer.h"
#include "Texture2D.h"
#include "../Drawables/WaterQuad.h"

namespace Devi
{
	class WaterRenderPass : public RenderPass
	{
	public:
	
		WaterRenderPass(int textureWidth, int textureHeight);
		void Execute() override;
	
	private:

		int m_textureWidth;
		int m_textureHeight;
		
		std::shared_ptr<FrameBuffer> m_reflectionFrameBuffer;
		std::shared_ptr<FrameBuffer> m_refractionFrameBuffer;
		
		std::shared_ptr<Texture2D> m_reflectionTexture;
		std::shared_ptr<Texture2D> m_refractionTexture;

	};
}