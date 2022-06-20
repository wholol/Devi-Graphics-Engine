#pragma once
#include "../src/IDrawable.h"
#include "../src/CubeMapTexture.h"
#include "BasicShapes/BasicShapesVertexData.h"
#include "../src/Shader.h"

namespace Devi
{
	class SkyBox : public Drawable
	{
	public:
		SkyBox(const std::string& name);
		void Draw() override;
	};
}