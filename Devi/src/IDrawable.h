#pragma once
#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "ITexture.h"
#include "../RenderPasses/RenderPass.h"
#include "../RenderPasses/RenderPassManager.h"
#include "../Materials/Material.h"

namespace Devi
{
	enum class RenderPassType;
	class RenderPassManager;
	/**
	* Drawable class. Objects that are drawn on the screen should inehrit this.
	*/
	class Drawable
	{

	public:
		Drawable(const std::string& name);
		
		virtual void Draw() = 0;
		
		std::string GetName() const;
	
		/**
		* Submits various variables to a specific render pass, which then uses them to render the renderable/drawable object.
		* @param renderPassManager the renderpass maanger instance.
		* @param stepNumber which step number should it be rendered in the render pass.
		* @param type type of render pass to pass the variables to.
		* @param shader the shader involved for this renderpass, step and this renderable/drawable object.
		* @param textures textures that will be used in the shader object passed. unsigned int is used by glActiveTextures
		* @param material the material of the drawable which will be used in the shader object passed.
		*/
		void SubmitToRenderPass(
			std::shared_ptr<RenderPassManager> renderPassManager, 
			unsigned int stepNumber,
			RenderPassType type, std::shared_ptr<Shader> shader, 
			std::optional<std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>> textures = {},
			std::optional<std::shared_ptr<Material>> material = {});
		
		const glm::mat4& GetModelMatrix() const;

	protected:
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;	//optional
		std::shared_ptr<VertexArray> m_vertexArray;

		std::string m_name;
		glm::mat4 m_modelMatrix{ glm::mat4(1.0) };
	};

	using DrawablePtr = std::shared_ptr<Drawable>;
}