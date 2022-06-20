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
	
		WaterRenderPass(int textureWidth, int textureHeight, int quadTextureWidth, int quadTextureHeight);
		void Execute() override;
	
	private:

		int m_textureWidth;
		int m_textureHeight;

		int m_quadTextureWidth;
		int m_quadTextureHeight;
		
		std::shared_ptr<FrameBuffer> m_reflectionFrameBuffer;
		std::shared_ptr<FrameBuffer> m_refractionFrameBuffer;
		
		std::shared_ptr<Texture2D> m_reflectionTexture;
		std::shared_ptr<Texture2D> m_refractionTexture;

		std::vector<float> m_vertexBuffer;

		std::shared_ptr<VertexBuffer> m_waterQuadVertexBuffer;
		std::shared_ptr<VertexArray> m_waterQuadVertexArray;
	};
}