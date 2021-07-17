#pragma once
#include "VertexArray.h"


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