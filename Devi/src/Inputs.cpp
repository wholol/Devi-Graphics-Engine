#include "Inputs.h"

namespace Devi
{
	Window* Inputs::m_window{ nullptr };

	void Inputs::Init(Window* window)
	{
		m_window = window;
	}

	bool Inputs::IsKeyPressed(DeviKey::Key key)
	{
		auto* window = m_window->GetWindow();
		return (glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS);
	}

	glm::highp_dvec2 Inputs::GetMousePosInWindow()
	{
		double xpos;
		double ypos;
		auto* window = m_window->GetWindow();
		glfwGetCursorPos(window, &xpos, &ypos);
		return glm::highp_dvec2(xpos, ypos);
	}
}
