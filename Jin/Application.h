#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
	~Application();

	bool Init(const ApplicationConfiguration& config);
	bool Run();
	bool IsOpen();
	
	void Tick();
	void SwapBuffers();
	void PollEvents();
	const Window& GetWindow() const { return m_window; }

private:
	bool InitGLEW();
	bool InitGLFW();
};