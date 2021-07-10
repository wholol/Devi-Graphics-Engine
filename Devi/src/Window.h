#pragma once
#include <glad/glad.h>
#include <glfw3.h>
#include <string>
#include <iostream>
#include "Log.h"

//GLFW callback functions here
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

namespace Devi
{
	/**
	* Window clas. Resposnible for initializing the glfw window context (and also load in GLAD).
	**/
	class Window
	{
	public:
		void Init(int screenWidth, int screenHeight, const std::string& titleName);
		GLFWwindow* GetWindow() const;
		void Shutdown();
		void Update();
	
	private:
		GLFWwindow* m_windowContext = nullptr;
	};

}