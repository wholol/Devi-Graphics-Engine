#pragma once
#include "RenderPass.h"
#include "ShadowMapRenderPass.h"

namespace Devi
{
	class ShadowMapRenderPass;

	class DefaultRenderPass : public RenderPass
	{
	public:

		DefaultRenderPass();
		void Execute() override;
	private:
		FrameBuffer m_framebuffer{ "t" };
		std::shared_ptr<Texture2D> m_depthTexture;
	};
}