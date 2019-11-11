#include <iostream>
#include "Application.h"
#include "Renderer2D.h"
#include <glm\ext\matrix_clip_space.hpp>

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
		for (int x = 0; x < 8; ++x)
		{
			for (int y = 0; y < 100; ++y)
			{
				renderer.DrawQuad({ 7 * x, 7 * y,0 }, { 14,14,1 }, { 1,x*0.2f,y*0.2f,1 });
			}
		}
		app.SwapBuffers();
	}
}