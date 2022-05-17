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
	};
}