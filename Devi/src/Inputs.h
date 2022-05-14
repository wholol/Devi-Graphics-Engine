#pragma once
#include "KeyEnums.h"
#include "Window.h"
#include "../Dependencies/Math/glm/glm.hpp"


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
		static glm::highp_dvec2 GetMousePosInWindow();
	private:
		static Window* m_window;

	};
}
