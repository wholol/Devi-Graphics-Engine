#pragma once
#include <string>
#include "../src/IDrawable.h"

namespace Devi
{
	/**
	* Height map class. tesselation of the height map done in CPU isntead of tesselation shader.
	*/
	class CPUHeightMap : public Drawable
	{
	public:
		CPUHeightMap(const std::string& name, const std::string& heightMapFilePath);
		void GenerateVertices(const std::string& heightMapFilePath);
		void Draw() override;

	private:
		int m_width, m_height;
		std::vector<float> m_vertices;
		std::vector<unsigned int> m_indices;
	};

}