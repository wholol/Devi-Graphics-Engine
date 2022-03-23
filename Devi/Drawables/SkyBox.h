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
		SkyBox(const std::string& rightTextureFilePath, const std::string& leftTextureFilePath,
			const std::string& topTextureFilePath, const std::string& bottomTextureFilePath,
			const std::string& frontTextureFilePath, const std::string& backTextureFilePath,
			const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

		void Draw() override;

	private:
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<VertexArray> m_vertexArray;
		CubeMapTexture m_cubeMapTexture;
		Shader m_skyBoxShader;
	};
}