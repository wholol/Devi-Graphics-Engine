#pragma once
/**
* Header with contains vertex data for basic shapes.
**/
namespace Devi
{
	namespace BasicShapes
	{
		//triangle with RGB colors on each vertex respectively.
		float v_TriangleWithColors[] = {
			// positions         // colors
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
		};
	}
}
