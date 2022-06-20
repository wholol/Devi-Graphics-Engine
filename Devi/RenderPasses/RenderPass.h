#pragma once
#include "../src/Shader.h"
#include "../src/ITexture.h"
#include <vector>
#include "../src/FrameBuffer.h"
#include "../src/IDrawable.h"
#include "../Materials/Material.h"
#include <unordered_map>
#include <functional>

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
		std::shared_ptr<Material> material;
	};

	/**
	* A step essentially contains a render queue, which contains a vector of shaders, textures, material and renderable objects.
	*/
	struct Step
	{
		std::vector<RenderPassObject> renderQueue;
	};

	/**
	* RenderPass class. Essentially the base class for various render pass operations.
	* Shaders, renderables, materials and textures are submitted to the RenderPass class, which stores these attributes and render them accordingly.
	*/
	class RenderPass
	{

	public:
		/**
		* Submit function. Submits a shader, textures, material, a renderable object and the stepnumbers it should be invovled in.
		* @note this function assumes has a unique shader for each step for the renderable object, hence it takes in a initializer list for stepNumbers.
		* @param shader shader to be used.
		* @param textures (optional) textures to be used.
		* @param material (optional) material to be used.
		* @param darawable a drawable object that uses the shader,textures and material specified.
		* @param stepNumber which step should it be in. Starts with 0.
		*/
		void Submit(std::shared_ptr<Shader> shader, const std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>>& textures,
			std::shared_ptr<Material> material,
			Drawable* drawable,
			unsigned int stepNumber);

		/**
		* Links (stores) another renderpass to this render pass.
		* @param renderpass anotehr renderpass to link to.
		*/
		void LinkRenderPass(std::shared_ptr<RenderPass> renderpass);
		
		/**
		* Gets the frameBuffer output for this render pass.
		* @param name name of the framebuffer that is needed.
		*/
		std::shared_ptr<FrameBuffer> GetFrameBuffer(const std::string& name) const;

		/**
		* Specify the render pass type.
		* @param renderPassType the type of render pass.
		*/
		void SetRenderPassType(RenderPassType renderPassType);

		template <typename T>
		void SortCriteria(std::function<T> sortCriteria, unsigned int stepNumber);

		template<typename T>
		inline void RenderPass::SortCriteria(std::function<T> sortCriteria, unsigned int stepNumber)
		{
			//TODO
		}

		/**
		* Get the step involved based on the step number provided.
		* @param stepNumber the stepNumber needed.
		* @note we do not have a getter for the number of steps as we have to explicitly specify the framebubber bindings based on the step number.
		*/
		const Step& GetStep(unsigned int stepNumber) const;

		RenderPassType GetRenderPassType() const;

		virtual void Execute() = 0;

	protected:
		std::unordered_map<unsigned int, Step> m_stepMap;	// stepMap contains the stepNumber and contains a vector of render pass objects (render queue).
		
		std::unordered_map<RenderPassType,std::shared_ptr<RenderPass>> m_dependencyRenderPasses;	//caches a list of renderpasses that requires this renderpass and vice versa.
			
		std::unordered_map<std::string, std::shared_ptr<FrameBuffer>> m_frameBufferMap;		//caches the framebuffer outputs for this render pass.

		RenderPassType m_renderPassType;	//type of render pass.
	};
	

}