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

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0,0,0 }) * glm::scale(glm::mat4(1.0f), {14, 14, 1});
	Texture t("textures/test.png");

	Transform trans;
	trans.SetPosition({ 400, 300, 0 });
	trans.SetScale({700,700,1});

	while (app.IsOpen())
	{
		app.PollEvents();
		app.Tick();

		renderer.Clear({0.8f, 0.8f, 0.8f, 1.0f});
		renderer.BeginScene();
		renderer.DrawQuad(trans, t);
		
		renderer.EndScene();

		app.SwapBuffers();
	}
}