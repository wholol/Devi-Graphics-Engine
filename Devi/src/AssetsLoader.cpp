#include "AssetsLoader.h"
#include "glad/glad.h"
#include "../Materials/PhongMaterialInstance.h"
#include "../Materials/PBRMaterialInstance.h"

namespace Devi
{
	
	Assets::Assets(std::shared_ptr<RenderPassManager> renderPassManager)
	{
		m_shaderManager = std::make_shared<ShaderManager>();
		m_textureManager = std::make_shared<TextureManager>();
		m_drawableManager = std::make_shared <DrawableManager>();

		m_renderPassManager = renderPassManager;
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
		return m_drawableManager->GetAllDrawables();
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

		m_shaderManager->addShader("DepthMap",
			"assets/Shaders/DepthMap_vs.glsl",
			"assets/Shaders/DepthMap_fs.glsl");

		m_shaderManager->addShader("TerrainDepthMap",
			"assets/Shaders/GPUHeight_vs.glsl",
			"assets/Shaders/DepthMap_fs.glsl",
			"assets/Shaders/GPUHeight_tcs.glsl",
			"assets/Shaders/GPUHeight_tes.glsl");

		m_shaderManager->addShader("Terrain",
			"assets/Shaders/GPUHeight_vs.glsl",
			"assets/Shaders/GPUHeight_fs.glsl",
			"assets/Shaders/GPUHeight_tcs.glsl",
			"assets/Shaders/GPUHeight_tes.glsl");
		
		m_shaderManager->addShader("BasicCube",
			"assets/Shaders/cubevs.glsl",
			"assets/Shaders/cubefs.glsl"
			);
	}

	void Assets::LoadDrawables()
	{

		//std::string skyboxName ="DayLightSkyBox";
		//auto skybox = std::make_shared<SkyBox>(skyboxName);
		//SetupDrawableShaderAndTextures(skybox, skyboxName, "DayLightSkyBoxCubeMap");
		////m_drawableManager->AddDrawable(skyboxName, skybox);	
		
		//shadow map pass
		auto depthMapShader = m_shaderManager->GetShader("DepthMap");
		
		std::string basicCubeName = "BasicCube";
		auto cube = std::make_shared<Cube>(basicCubeName);
		m_drawableManager->AddDrawable(basicCubeName, cube);
		cube->SubmitToRenderPass(m_renderPassManager, RenderPassType::ShadowMap, depthMapShader);
		
		std::string Terrain = "Terrain";
		auto heightMapTexture = std::dynamic_pointer_cast<Texture2D>(m_textureManager->GetTexture("heightMap"));

		auto heightMapGPU = std::make_shared<GPUHeightMap>(Terrain);
		heightMapGPU->GenerateVertices(heightMapTexture);
		std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures;
		
		textures.push_back(std::make_pair(m_textureManager->GetTexture("heightMap"), 0));
		heightMapGPU->SubmitToRenderPass(m_renderPassManager, RenderPassType::ShadowMap, m_shaderManager->GetShader("TerrainDepthMap"), textures);
		
		m_drawableManager->AddDrawable(Terrain, heightMapGPU);

		//auto orangeShader = m_shaderManager->GetShader(basicCubeName);
		//std::shared_ptr<Material> orange;
		//orange = std::make_shared<Material>("BasicCubeColor",glm::vec4(0.0f,1.0f,0.0f,1.0f));
		//std::shared_ptr<PhongMaterialInstance> orangeInstance = std::make_shared<PhongMaterialInstance>("", orange);
		//cube->SubmitToRenderPass(m_renderPassManager, RenderPassType::Default, orangeShader, {} , orangeInstance);
		
		textures.push_back(std::make_pair(m_textureManager->GetTexture("grass"), 1));
		heightMapGPU->SubmitToRenderPass(m_renderPassManager, RenderPassType::Default, m_shaderManager->GetShader("Terrain"),
			textures);
		

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
		m_textureManager->AddTexture2D("heightMap", "assets/Textures/iceland_heightmap.png", textureParams, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
		textureParams.clear();

		m_textureManager->AddCubeMapTexture("DayLightSkyBoxCubeMap",
			"assets/Textures/Daylight Box_Right.bmp", "assets/Textures/Daylight Box_Left.bmp",
			"assets/Textures/Daylight Box_Top.bmp", "assets/Textures/Daylight Box_Bottom.bmp",
			"assets/Textures/Daylight Box_Front.bmp", "assets/Textures/Daylight Box_Back.bmp");
		textureParams.clear();
	}
}

