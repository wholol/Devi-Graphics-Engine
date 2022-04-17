#include "SkyBox.h"

namespace Devi
{
	SkyBox::SkyBox(const std::string& name)
		:m_name(name)
	{
		m_vertexBuffer = std::make_unique<VertexBuffer>(BasicShapesVertexData::Get(BasicShape::CUBE));
		m_vertexBuffer->AddAttribLayout(3);
		m_vertexArray = std::make_unique<VertexArray>(*m_vertexBuffer);
	}

	void SkyBox::Draw()
	{
		m_skyBoxShader->Bind();

		for (const auto& texture : m_textures)
		{
			texture.first->Bind( texture.second );
		};

		glDepthFunc(GL_LEQUAL);
		
		Renderer::RenderWithoutIndexBuffers(12, *m_vertexArray, *m_skyBoxShader,glm::mat4(1.0),true);
		glDepthFunc(GL_LESS);
	}

	void SkyBox::SetShader(std::shared_ptr<Shader> shader)
	{
		m_skyBoxShader = shader;
	}

	void SkyBox::SetTextures(std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures)
	{
		m_textures = std::move(textures);
		m_skyBoxShader->Bind();

		for (auto& t : textures)
		{
			m_skyBoxShader->SetUniform(t.first->GetName(), t.second, UniformDataType::INT);
		};
	}
}

