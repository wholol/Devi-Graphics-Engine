#pragma once
#include <utility>
#include "../src/NotImplementedException.h"
#include "../src/Log.h"
#include <iostream>

namespace Devi
{
	enum class BasicShape
	{
		CUBE,
		RECTANGLE,
		SPHERE,
		TRIANGLE,
		TRIANGLERGB,
		RECTANGLERGBTEXCOORDS,
		TEXTUREDQUAD,
	};

	class BasicShapesVertexData
	{
	public:
		static std::pair<void*,size_t> Get(BasicShape basicShapeType);
	};
}
