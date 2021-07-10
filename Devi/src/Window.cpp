#include "Window.h"


void Devi::Window::Init(int screenWidth, int screenHeight, const std::string& windowTitle)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_windowContext = glfwCreateWindow(screenWidth, screenHeight, windowTitle.c_str(), nullptr, nullptr);

	if (!m_windowContext)
	{
		DEVI_FATAL("Window Creation Failed.", __FILE__, __LINE__);
	}

	glfwMakeContextCurrent(m_windowContext);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		DEVI_ERROR("gladLoader failed to initialize.", __FILE__, __LINE__);
	}

	glViewport(0, 0, screenWidth, screenHeight);

	glfwSetFramebufferSizeCallback(m_windowContext, FrameBufferSizeCallback);
}

GLFWwindow* Devi::Window::GetWindow() const
{
	return m_windowContext;
}

void Devi::Window::Shutdown()
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

