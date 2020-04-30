#pragma once
#include "pch.h"
#include "OrthographicCamera.h"
#include "Layer.h"


struct ApplicationConfiguration
{
	i32 Width, Height;
	cstr Title;
	bool Vsync;
};

class Application
{
    private:
	static Application* m_instance;
	ApplicationConfiguration m_appConfig;
	GLFWwindow* m_window;
	bool m_isOpen;
	f32 m_lastFrameTime = 0.0f;
	std::unordered_map<cstr, Layer*> m_layers;
    std::unordered_map<cstr, void*> m_layersSharedData;
    
    public:
	Application();
	~Application();
    
	static Application* Get() { return m_instance; }
    
    bool Init(const ApplicationConfiguration& config);
    bool Run();
    
    void AddLayer(Layer* layer);
    void RemoveLayer(Layer* layer);
    GLFWwindow* GetWindow() const { return m_window; }
    ApplicationConfiguration* GetConfig() { return &m_appConfig; }
    
    private:
    bool InitGLEW();
    bool InitGLFW();
};
