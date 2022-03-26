#include "SkyBox.h"

namespace Devi
{
	SkyBox::SkyBox(const std::string& rightTextureFilePath, const std::string& leftTextureFilePath,
		const std::string& topTextureFilePath, const std::string& bottomTextureFilePath,
		const std::string& frontTextureFilePath, const std::string& backTextureFilePath,
		const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		m_vertexBuffer = std::make_unique<VertexBuffer>(BasicShapesVertexData::Get(BasicShape::CUBE));
		m_vertexBuffer->AddAttribLayout(3);
		m_vertexArray = std::make_unique<VertexArray>(*m_vertexBuffer);

		//Note: do not change the order in which the filepath is added.
		m_cubeMapTexture.addCubeMapTextures(rightTextureFilePath);
		m_cubeMapTexture.addCubeMapTextures(leftTextureFilePath);

		m_cubeMapTexture.addCubeMapTextures(topTextureFilePath);
		m_cubeMapTexture.addCubeMapTextures(bottomTextureFilePath);

		m_cubeMapTexture.addCubeMapTextures(frontTextureFilePath);
		m_cubeMapTexture.addCubeMapTextures(backTextureFilePath);

		m_cubeMapTexture.GenerateCubeMap();

		m_skyBoxShader.SetShaderFilePath(vertexShaderFilePath, fragmentShaderFilePath);

	}

	void SkyBox::Draw()
	{
		m_skyBoxShader.Bind();
		m_cubeMapTexture.Bind();
		glDepthFunc(GL_LEQUAL);
		m_skyBoxShader.SetUniform("cubeMap", 0, UniformDataType::INT);
		Renderer::RenderWithoutIndexBuffers(12, *m_vertexArray, m_skyBoxShader,glm::mat4(1.0),true);
		glDepthFunc(GL_LESS);
	}
}

