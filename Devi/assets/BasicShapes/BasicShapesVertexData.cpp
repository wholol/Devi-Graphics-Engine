#include "BasicShapesVertexData.h"


float v_triangleRGB[] = 
{
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

float v_triangle[] =
{
	-0.5f, -0.5f, 0.0f, // left  
	0.5f, -0.5f, 0.0f, // right 
	0.0f,  0.5f, 0.0f  // top   
};

std::pair<void*, size_t> Devi::BasicShapesVertexData::Get(BasicShape basicShapeType)
{
	try
	{
		if (basicShapeType == BasicShape::TRIANGLERGB)
		{
			return std::make_pair((void*)v_triangleRGB, sizeof(v_triangleRGB));
		}

		else if (basicShapeType == BasicShape::TRIANGLE)
		{
			return std::make_pair((void*)v_triangle, sizeof(v_triangle));
		}

		else
		{
			throw Exception::NotImplementedException("Basic shape not implemented.", __FILE__, __LINE__);
			return std::pair<void*, size_t>();
		}
	}
	catch (const std::exception& e)
	{
		DEVI_ERROR(e.what(), __FILE__, __LINE__);
	}

	return std::pair<void*, size_t>();
}