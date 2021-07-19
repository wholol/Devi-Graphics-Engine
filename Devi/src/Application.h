#pragma once
#include "Window.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture2D.h"
#include <any>
#include <utility>
#include "Log.h"

namespace Devi
{
	class Application {

	public:
		
		void Init(int screenWidth, int screenHeight, const std::string& title);
		void Run();
		void ShutDown();

	private:
		Window m_window;
		bool m_isRunning = true;
	};
}
