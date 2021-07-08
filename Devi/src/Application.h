#pragma once
#include "Window.h"

namespace Devi
{

	class Application {

	public:
		
		void Init(int screenWidth, int screenHeight, const std::string& title);
		void Run();
		void ShutDown();

	private:
		Devi::Window m_window;
		bool m_isRunning = true;
	};
}
