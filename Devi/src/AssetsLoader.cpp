#include "AssetsLoader.h"
#include "glad/glad.h"
#include "../Materials/PhongMaterial.h"
#include "../Materials/PBRMaterial.h"
#include "../Noise/PerlinNoise.h"
#include "BindingLocation.h"
#include "TextureManager.h"

namespace Devi
{
	
	Assets::Assets(std::shared_ptr<RenderPassManager> renderPassManager)
	{
		m_shaderManager = std::make_shared<ShaderManager>();
		m_textureManager = std::make_shared<TextureManager>();
		m_materialManager = std::make_shared<MaterialManager>();
		m_drawableManager = std::make_shared <DrawableManager>();

		m_renderPassManager = renderPassManager;
	}

	void Assets::LoadAssets()
	{
		
		LoadShaders();
		LoadTextures();
		LoadMaterials();
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

		m_shaderManager->addShader("TerrainWater",
			"assets/Shaders/GPUHeight_vs.glsl",
			"assets/Shaders/GPUHeight_fs.glsl",
			"assets/Shaders/GPUHeight_tcs.glsl",
			"assets/Shaders/waterRenderingForTerrain_tes.glsl");
	}

	void Assets::LoadDrawables()
	{
		std::string skyboxName ="DayLightSkyBox";
		auto skybox = std::make_shared<SkyBox>(skyboxName);
		m_drawableManager->AddDrawable(skyboxName, skybox);	
		//skybox->SubmitToRenderPass(m_renderPassManager,0, RenderPassType::Default ,m_shaderManager->GetShader("DayLightSkyBox"));
	
		auto depthMapShader = m_shaderManager->GetShader("DepthMap");
		
		std::string basicCubeName = "BasicCube";
		auto cube = std::make_shared<Cube>(basicCubeName);
		m_drawableManager->AddDrawable(basicCubeName, cube);
		cube->SubmitToRenderPass(m_renderPassManager, 0, RenderPassType::ShadowMap, depthMapShader);
		cube->SubmitToRenderPass(m_renderPassManager, 0, RenderPassType::Default, m_shaderManager->GetShader(basicCubeName), {}, m_materialManager->GetMaterial("BasicCubeColor"));
		//cube->SubmitToRenderPass(m_renderPassManager, 0, RenderPassType::Water,);
		//cube->SubmitToRenderPass(m_renderPassManager, 1, RenderPassType::Water, );
		
		std::string terrainName = "Terrain";
		auto heightMapTexture = std::dynamic_pointer_cast<Texture2D>(m_textureManager->GetTexture("heightMap"));

		auto heightMapGPU = std::make_shared<GPUHeightMap>(terrainName);
		heightMapGPU->GenerateVertices(heightMapTexture);
		m_drawableManager->AddDrawable(terrainName, heightMapGPU);

		std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures;
		textures.push_back(std::make_pair(heightMapTexture, DEVI_UNIFORM_HEIGHTMAP));
		
		heightMapGPU->SubmitToRenderPass(m_renderPassManager, 0, RenderPassType::ShadowMap, m_shaderManager->GetShader("TerrainDepthMap"), textures);
		heightMapGPU->SubmitToRenderPass(m_renderPassManager, 0, RenderPassType::Default, m_shaderManager->GetShader("Terrain"), textures, m_materialManager->GetMaterial("grass"));
		heightMapGPU->SubmitToRenderPass(m_renderPassManager, 0, RenderPassType::Water, m_shaderManager->GetShader("TerrainWater"), textures, m_materialManager->GetMaterial("grass"));
		heightMapGPU->SubmitToRenderPass(m_renderPassManager, 1, RenderPassType::Water, m_shaderManager->GetShader("TerrainWater"), textures, m_materialManager->GetMaterial("grass"));	

		std::string waterName = "WaterQuad";
		auto water = std::make_shared<WaterQuad>(waterName, heightMapTexture->GetTextureWidth(), heightMapTexture->GetTextureHeight());
		m_drawableManager->AddDrawable(waterName, water);

		//add all objects (cube and terrain) into water render pass to be used to render to framebuffers for reflection an refraction.
		//add watrer quad in normal render pass (antoehr shader taht will use the framebuffer outputs

	}

	void Assets::LoadTextures()
	{
		//take note of https://www.reddit.com/r/opengl/comments/5rx2cn/nvoglvdll_cant_find_or_open_the_pdb_file/. caused by incorrect format. (eg GL_RGBA instead of GL_RGB)

		std::vector<TextureParamsSpecification> textureParams;

		m_textureManager->AddCubeMapTexture("DayLightSkyBoxCubeMap",
			"assets/Textures/SkyBox/Daylight Box_Right.bmp", "assets/Textures/SkyBox/Daylight Box_Left.bmp",
			"assets/Textures/SkyBox/Daylight Box_Top.bmp", "assets/Textures/SkyBox/Daylight Box_Bottom.bmp",
			"assets/Textures/SkyBox/Daylight Box_Front.bmp", "assets/Textures/SkyBox/Daylight Box_Back.bmp");
		textureParams.clear();

		//terrain texture
		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("grass", "assets/Textures/Terrain/grassAlbedo.png", textureParams, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		textureParams.clear();

		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("grassAO", "assets/Textures/Terrain/grassAO.png", textureParams, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		textureParams.clear();

		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("grassMetallic", "assets/Textures/Terrain/grassMetallic.png", textureParams, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		textureParams.clear();

		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("grassNormalMap", "assets/Textures/Terrain/grassNormalMap.png", textureParams, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		textureParams.clear();

		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("grassRoughness", "assets/Textures/Terrain/grassRoughness.png", textureParams, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		textureParams.clear();

		//snow
		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("snow", "assets/Textures/Terrain/snowAlbedo.png", textureParams, GL_RGBA, GL_RGBA ,GL_UNSIGNED_BYTE);
		textureParams.clear();

		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("snowAO", "assets/Textures/Terrain/snowAO.png", textureParams, GL_RGB8, GL_RGB8, GL_UNSIGNED_BYTE);
		textureParams.clear();

		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("snowMetallic", "assets/Textures/Terrain/goldMetallic.psd", textureParams, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
		textureParams.clear();

		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("snowRoughness", "assets/Textures/Terrain/snowRoughness.png", textureParams, GL_RGB8, GL_RGB8, GL_UNSIGNED_BYTE);
		textureParams.clear();
		
		textureParams.push_back({ GL_TEXTURE_WRAP_R, GL_REPEAT });
		textureParams.push_back({ GL_TEXTURE_WRAP_S, GL_REPEAT });
		m_textureManager->AddTexture2D("heightMap", "assets/Textures/Terrain/perlinNoise.png", textureParams, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
		textureParams.clear();

		//PerlinNoise perlin(2000, 2000);
		//perlin.Generate("assets/Textures/PerlinNoise.bmp");
		
		
	}

	void Assets::LoadMaterials()
	{
		std::shared_ptr<PhongMaterial> basicCubeColor = std::make_shared<PhongMaterial>("BasicCubeColor", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		m_materialManager->AddMaterial(basicCubeColor);

		std::shared_ptr<PBRMaterial> terrainMaterial = std::make_shared<PBRMaterial>("grass", m_textureManager->GetTexture("grass"));
		terrainMaterial->SetMetallic(m_textureManager->GetTexture("grassMetallic"));
		terrainMaterial->SetAo(m_textureManager->GetTexture("grassAO"));
		terrainMaterial->SetRoughness(m_textureManager->GetTexture("grassRoughness"));
		terrainMaterial->SetNormalMap(m_textureManager->GetTexture("grassNormalMap"));
		m_materialManager->AddMaterial(terrainMaterial);
	}
}

