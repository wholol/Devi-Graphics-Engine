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
}
