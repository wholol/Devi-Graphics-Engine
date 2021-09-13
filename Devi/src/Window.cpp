#include "Window.h"

namespace Devi
{
	void Window::Init(int screenWidth, int screenHeight, const std::string& windowTitle)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_windowContext = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), nullptr, nullptr);

		if (!m_windowContext)
		{
			DEVI_FATAL("Window Creation Failed.", __FILE__, __LINE__);
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_windowContext);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			DEVI_FATAL("gladLoader failed to initialize.", __FILE__, __LINE__);
			glfwTerminate();
		}

		DEVI_INFO("Window nad GLAD loader succesfully initialized.", __FILE__, __LINE__);

		glViewport(0, 0, screenWidth, screenHeight);

		glfwSetFramebufferSizeCallback(m_windowContext, FrameBufferSizeCallback);
	}

	GLFWwindow* Window::GetWindow() const
	{
		return m_windowContext;
	}

	void Window::Shutdown()
	{
		glfwTerminate();
		DEVI_INFO("Shutting Down the Window.", __FILE__, __LINE__);
	}

	void Devi::Window::Update()
	{
		glfwSwapBuffers(m_windowContext);
		glfwPollEvents();
	}

	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}
