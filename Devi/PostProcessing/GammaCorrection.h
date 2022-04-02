#pragma once
#include "../src/FrameBuffer.h"
#include "../src/Shader.h"
#include "../src/Texture2D.h"
#include "../src/RenderBuffer.h"

namespace Devi
{
	class GammaCorrection
	{
	public:
		GammaCorrection(int screenWidth, int screenHeight, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void RenderToTexture();
	private:
		int m_screenWidth;
		int m_screenHeight;
		FrameBuffer m_framebuffer;
		RenderBuffer m_renderBuffer;
		Texture2D m_texture2D;
		Shader m_shader;
	};
}
	