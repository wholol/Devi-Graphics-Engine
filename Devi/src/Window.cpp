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
		std::cerr << "window creating failed." << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_windowContext);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "GLAD failed to initialize." << std::endl;
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
}

void Devi::Window::Update()
{
	glfwSwapBuffers(m_windowContext);
	glfwPollEvents();
}

void FrameBufferSizeCallback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

