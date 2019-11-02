#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.h"

struct ApplicationConfiguration
{
	int width, height;
	const char* title;
	bool vsync;
};

class Application
{
private:
	ApplicationConfiguration m_appConfig;
	Window m_window;
	bool m_isOpen;
public:
	Application();

	bool Init(const ApplicationConfiguration& config);
	bool Run();
	bool IsOpen();
	
	void Tick();
	void SwapBuffers();
	void PollEvents();

private:
	bool InitGLEW();
	bool InitGLFW();
};