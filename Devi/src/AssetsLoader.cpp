#include "AssetsLoader.h"
#include "glad/glad.h"

namespace Devi
{
	Assets::Assets()
	{
		m_shaderManager = std::make_shared<ShaderManager>();
		m_textureManager = std::make_shared<TextureManager>();
		m_drawableManager = std::make_shared <DrawableManager>();
	}
	
	void Assets::LoadAssets()
	{
		LoadShaders();
		LoadTextures();
		LoadDrawables();
	}

	std::shared_ptr<ShaderManager> Assets::GetShaderManager() const
	{
		return m_shaderManager;
	}

	std::shared_ptr<TextureManager> Assets::GetTextureManager() const
	{
		return m_textureManager;
	}

	std::shared_ptr<DrawableManager> Assets::GetDrawableManager() const
	{
		return m_drawableManager;
	}

	const std::vector<DrawablePtr>& Assets::GetDrawables() const
	{
		return m_drawables;
	}

	void Assets::LoadShaders()
	{
		m_shaderManager->addShader("CPUHeightMap",
			"assets/Shaders/CPUHeightmap_vs.glsl",
			"assets/Shaders/CPUHeightmap_fs.glsl");

		m_shaderManager->addShader("GPUHeightMap",
			"assets/Shaders/GPUHeight_vs.glsl",
			"assets/Shaders/GPUHeight_fs.glsl",
			"assets/Shaders/GPUHeight_tcs.glsl",
			"assets/Shaders/GPUHeight_tes.glsl");

		m_shaderManager->addShader("DayLightSkyBox",
			"assets/Shaders/skybox_vs.glsl",
			"assets/Shaders/skybox_fs.glsl");
	}

	void Assets::LoadDrawables()
	{
	
		std::string GPUHeightMapName = "GPUHeightMap";
		auto HeightMapGPU = std::make_shared<GPUHeightMap>(GPUHeightMapName, "assets/Textures/iceland_heightmap.png");
		SetupDrawableShaderAndTextures(HeightMapGPU, "GPUHeightMap","icelandHeightMap","grass");
		m_drawableManager->AddDrawable(GPUHeightMapName, HeightMapGPU);
		m_drawables.push_back(HeightMapGPU);
		
		std::string skyboxName ="DayLightSkyBox";
		auto skybox = std::make_shared<SkyBox>(skyboxName);
		SetupDrawableShaderAndTextures(skybox, skyboxName, "DayLightSkyBoxCubeMap");
		m_drawableManager->AddDrawable(skyboxName, skybox);
		m_drawables.push_back(skybox);
		
	}

	void Assets::LoadTextures()
	{
		std::vector<TextureParamsSpecification> textureParams;
		
		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("grass", "assets/Textures/grass.png", textureParams, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		textureParams.clear();

		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("icelandHeightMap", "assets/Textures/iceland_heightmap.png", textureParams, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
		textureParams.clear();

		m_textureManager->AddCubeMapTexture("DayLightSkyBoxCubeMap",
			"assets/Textures/Daylight Box_Right.bmp", "assets/Textures/Daylight Box_Left.bmp",
			"assets/Textures/Daylight Box_Top.bmp", "assets/Textures/Daylight Box_Bottom.bmp",
			"assets/Textures/Daylight Box_Front.bmp", "assets/Textures/Daylight Box_Back.bmp");
	}
}

