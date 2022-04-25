#pragma once
#include "../src/IDrawable.h"
#include "../src/CubeMapTexture.h"
#include "BasicShapes/BasicShapesVertexData.h"
#include "../src/Shader.h"

namespace Devi
{
	class SkyBox : public IDrawable
	{
	public:
		SkyBox(const std::string& name);
		void Draw() override;
		void SetShader(std::shared_ptr<Shader> shader) override;
		void SetTextures(std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> textures) override;
		std::string GetName() const override;

	private:
		std::string m_name;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<VertexArray> m_vertexArray;
		std::shared_ptr<Shader> m_skyBoxShader;
		std::vector<std::pair<std::shared_ptr<ITexture>, unsigned int>> m_textures;
	};
}