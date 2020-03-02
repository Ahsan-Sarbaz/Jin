#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "OrthographicCamera.h"
#include "Window.h"
#include "Layer.h"


struct ApplicationConfiguration
{
	int width, height;
	const char* title;
	bool vsync;
};

class Application
{
private:
	static Application* m_instance;
	ApplicationConfiguration m_appConfig;
	Window m_window;
	bool m_isOpen;
	float m_lastFrameTime = 0.0f;
	std::map<const char*, Layer*> m_layers;

public:
	Application();
	~Application();

	static Application* Get() { return m_instance; }

	bool Init(const ApplicationConfiguration& config);
	bool Run();
	
	void AddLayer(Layer* layer);
	void RemoveLayer(Layer* layer);
	const Window& GetWindow() const { return m_window; }

private:
	bool InitGLEW();
	bool InitGLFW();
};