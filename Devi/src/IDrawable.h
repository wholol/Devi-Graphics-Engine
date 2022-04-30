#pragma once
#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "ITexture.h"
#include "RenderPass.h"

namespace Devi
{
	enum class RenderPassType;

	/**
	* Drawable class. Objects that are drawn on the screen should inehrit this.
	*/
	class Drawable
	{
	public:
		Drawable(const std::string& name);
		virtual void Draw() = 0;
		std::string GetName() const;
		virtual void AddToRenderPass(RenderPassType type, std::shared_ptr<Shader> shader, const std::vector<std::shared_ptr<std::pair<ITexture, unsigned int>>>& textures)
		{
		}

	protected:
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;	//optional
		std::shared_ptr<VertexArray> m_vertexArray;

		std::string m_name;

		glm::mat4 m_modelMatrix{ glm::mat4(1.0) };
	};

	using DrawablePtr = std::shared_ptr<Drawable>;
}