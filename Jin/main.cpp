#include <iostream>
#include "Application.h"
#include "Shader.h"

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

	Shader s("shaders/vs.glsl", "shader/fs.glsl");

	while (app.IsOpen())
	{
		app.PollEvents();
		app.Tick();
		app.SwapBuffers();
	}
}