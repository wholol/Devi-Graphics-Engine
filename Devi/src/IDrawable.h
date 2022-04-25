#pragma once
#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "ITexture.h"

namespace Devi
{
	
	/**
	* Drawable interface class. Objects that are drawn on the screen should inehrit this.
	*/
	class IDrawable
	{
	public:

		virtual void Draw() = 0;
		virtual void SetShader(std::shared_ptr<Shader> shader) = 0;
		virtual void SetTextures(std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures) = 0;
		virtual std::string GetName() const = 0;
		virtual void SetDepthMapTexture(std::shared_ptr<ITexture> depthMap)
		{
		};

		virtual void SetLightSpaceMatrix(glm::mat4 lightSpaceMatrix)
		{

		};


	};

	using DrawablePtr = std::shared_ptr<IDrawable>;
}