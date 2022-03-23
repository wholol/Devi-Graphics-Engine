#pragma once
#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Shader.h"

namespace Devi
{
	/**
	* Drawable interface class. Objects that are drawn on the screen should inehrit this.
	*/
	class IDrawable
	{
	public:

		virtual void Draw() = 0;

	};
}