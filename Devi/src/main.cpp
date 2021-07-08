#include "Shader.h"
#include "VertexBuffer.h"
#include <glad/glad.h>
#include <glfw3.h>
#include "Application.h"

int main()
{
	Devi::Application app;
	app.Init(800, 600, "Devi Renderer");
	app.Run();

	return 0;
}