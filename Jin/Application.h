#pragma once
#include "Defines.h"
#include "Types.h"
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
	i32 width, height;
	cstr title;
	bool vsync;
};

class Application
{
private:
	static Application* m_instance;
	ApplicationConfiguration m_appConfig;
	Window m_window;
	bool m_isOpen;
	f32 m_lastFrameTime = 0.0f;
	std::map<cstr, Layer*> m_layers;

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