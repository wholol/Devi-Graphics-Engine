#pragma once
#include <string>
#include "../src/IDrawable.h"
#include "../src/Texture2D.h"
#include "../Light/Light.h"
#include "../RenderPasses/RenderPassManager.h"
#include <algorithm>

namespace Devi
{
	// utilizes the tesellation shader to render a height map.
	class GPUHeightMap : public Drawable
	{
	public:
		GPUHeightMap(const std::string& name);
		void GenerateVertices(std::shared_ptr<Texture2D> heightMapTexture);
		void Draw() override;

	private:
		int m_width;
		int m_height;
		std::vector<float> m_vertices;
		int m_numTiles = 0;
	};
}