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
	config.vsync = 1;
	
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
		renderer.DrawQuad({ 0,0,0 }, { 100,100,1 }, { 0,1,1,1 });
		renderer.DrawQuad({ 500,100,0 }, { 100,100,1 }, { 0,0,1,1 });
		app.SwapBuffers();
	}
}