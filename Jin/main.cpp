#include <iostream>
#include "Application.h"
#include "Renderer2D.h"
#include <glm\ext\matrix_clip_space.hpp>
#include "Input.h"

int main()
{
	Application app;
	ApplicationConfiguration config = {};
	
	config.width = 800;
	config.height = 600;
	config.title = "Window";
	config.vsync = 0;
	
	if (!app.Init(config)) return 1;
	if (!app.Run()) return 2;

	Renderer2D renderer;
	RendererConfig rendererConfig = {};
	rendererConfig.projectionMatrix = glm::ortho(0.0f, (float)config.width, (float)config.height, 0.0f, -1.0f, 1.0f);
	renderer.Init(rendererConfig);

	while (app.IsOpen())
	{
		app.PollEvents();
		app.Tick();

		renderer.Clear({0.8f, 0.8f, 0.8f, 1.0f});
		
		renderer.BeginScene();

		renderer.EndScene();

		app.SwapBuffers();
	}
}