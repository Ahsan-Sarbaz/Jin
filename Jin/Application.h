#pragma once
#include "Defines.h"
#include "Types.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <map>
#include "OrthographicCamera.h"
#include "Window.h"
#include "Layer.h"
#include "Jin_imgui.h"
#include "DX11.h"

enum class GraphicsAPI
{
	DX11,
	OpenGL
};

struct ApplicationConfiguration
{
	i32 width, height;
	cstr title;
	bool vsync;
	GraphicsAPI api;
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
	JIN_INLINE const Window& GetWindow() const { return m_window; }
	JIN_INLINE static const ApplicationConfiguration GetConfig() { return m_instance->m_appConfig; }

private:
	bool InitGLEW();
	bool InitGLFW();
};