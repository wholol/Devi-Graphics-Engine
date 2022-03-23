#pragma once
#include "KeyEnums.h"
#include "Window.h"

namespace Devi
{
	/**
	* Inputs class. contains glfw callbacks for handling events.
	*/
	class Inputs
	{
	public:
		static void Init(Window* window);
		static bool IsKeyPressed(DeviKey::Key key);

	private:
		static Window* m_window;

	};
}
