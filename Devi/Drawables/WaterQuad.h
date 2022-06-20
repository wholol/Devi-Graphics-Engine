#pragma once
#include "IDrawable.h"

namespace Devi
{
	class WaterQuad : public Drawable
	{
	public:
		//TODO: use numTiles
		WaterQuad(const std::string& name, int width, int height, int numTiles = 0);
		void Draw() override;


	private:
		int m_width, m_height;
		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;
	};
}