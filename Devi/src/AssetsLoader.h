#pragma once
#include "TextureManager.h"
#include "ShaderManager.h"
#include "DrawableManager.h"
#include "GPUHeightMap.h"
#include "SkyBox.h"
#include "Cube.h"
#include <type_traits>

namespace Devi
{
	/**
	* Class responsible for loading assets for the engine.
	*/
	class Assets
	{
	public:
		
		Assets();
		void LoadAssets();
		std::shared_ptr<ShaderManager> GetShaderManager() const;
		std::shared_ptr<TextureManager> GetTextureManager() const;
		std::shared_ptr<DrawableManager> GetDrawableManager() const;
		const std::vector<DrawablePtr>& GetDrawables() const;
		 
		// https://stackoverflow.com/questions/39659127/restrict-variadic-template-arguments
		template< typename ...TextureNames, class Enable = std::enable_if_t<(... && std::is_same_v<TextureNames, const char*>)> >
		inline void SetupDrawableShaderAndTextures(DrawablePtr drawable,const std::string& shaderName, TextureNames ...args)
		{
			auto shader = m_shaderManager->GetShader(shaderName);
			drawable->SetShader(shader);
			SetDrawableTexture(args...);
			drawable->SetTextures(m_texturesForDrawable);
			m_texturesForDrawable.clear();
		}


	private:
		
		void LoadShaders();
		void LoadDrawables();
		void LoadTextures();

		template<typename TextureName, typename ...TextureNames>
		inline void SetDrawableTexture(TextureName texturename, TextureNames ...args)
		{
			auto texture = m_textureManager->GetTexture(texturename);
			m_texturesForDrawable.push_back(std::pair{ texture , m_textureUniformBinding });
			++m_textureUniformBinding;
			SetDrawableTexture(args...);
		}

		//handle base case of variadic template
		void SetDrawableTexture()
		{
			m_textureUniformBinding = 0;
		}

		std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> m_texturesForDrawable;
		unsigned int m_textureUniformBinding = 0;

		std::shared_ptr<ShaderManager> m_shaderManager;
		std::shared_ptr<TextureManager> m_textureManager;
		std::shared_ptr<DrawableManager> m_drawableManager;	
	};
	



}