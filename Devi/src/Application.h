#pragma once
#include "Window.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture2D.h"
#include <any>
#include <utility>
#include "Log.h"
#include "Camera.h"
#include "Inputs.h"
#include "Scene.h"
#include "AssetsLoader.h"

namespace Devi
{
	class Application 
	{

	public:
		Application(int screenWidth, int screenHeight, const std::string& title);
		void Run();
		void ShutDown();

	private:
		Camera m_camera{glm::vec3(0.0,0.0,0.0)};
		int m_screenWidth;
		int m_screenHeight;
		Window m_window;
		bool m_isRunning = true;
		std::unique_ptr<Scene> m_scene{nullptr};
		std::shared_ptr<RenderPassManager> m_renderPassManager;
		std::shared_ptr<Assets> m_assets;
		double lastTime = 0.0;
		double deltaTime = 0.0;
	};
}
