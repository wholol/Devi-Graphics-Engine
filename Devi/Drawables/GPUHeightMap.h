#pragma once
#include <string>
#include "../src/IDrawable.h"

namespace Devi
{
	// utilizes the tesellation shader to render a height map.
	class GPUHeightMap : public IDrawable
	{
	public:
		GPUHeightMap(const std::string& heightMapFilePath, const std::string& vertexShaderFilePath,
			const std::string& fragmentShaderFilePath);
		void Draw() override;

	private:

	};
}