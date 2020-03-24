#include "Application.h"
#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include "Time.h"

#define JIN_IMGUI 1

Application* Application::m_instance = nullptr;

Application::Application()
{
	m_instance = this;
}

Application::~Application()
{
#if JIN_IMGUI
	ShutdownJinImGui();
#endif // JIN_NO_IMGUI
}

static void window_size_callback(GLFWwindow* window, i32 width, i32 height)
{
	glViewport(0, 0, width, height);
}

bool Application::Init(const ApplicationConfiguration& config)
{
	m_appConfig = config;
	
	if (!InitGLFW()) return false;
	
	WindowConfig windowConfig = {};
	windowConfig.width = m_appConfig.width;
	windowConfig.height = m_appConfig.height;
	windowConfig.title = m_appConfig.title;
	
	if (!m_window.Init(windowConfig)) return false;
	
	if (m_appConfig.api == GraphicsAPI::OpenGL)
		if (!InitGLEW()) return false;

	m_isOpen = true;

	glfwSetWindowSizeCallback(m_window.GetHandle(), window_size_callback);

	DX11Config dx11Config = {};
	dx11Config.width = m_appConfig.width;
	dx11Config.height = m_appConfig.height;
	dx11Config.windowHanlde = m_window.GetHandleWin32();
	DX11::Init(dx11Config);

#if JIN_IMGUI
	InitJinImgui((IMGUIGraphicsAPI)m_appConfig.api, DX11::GetDevice(), DX11::GetContext(), m_window.GetHandle(), m_window.GetHandleWin32());
#endif // JIN_IMGUI

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	
	glfwSwapInterval(m_appConfig.vsync ? 1 : 0);

	return true;
}

bool Application::Run()
{
	for (auto layer : m_layers)
	{
		layer.second->Start();
	}

	while (!glfwWindowShouldClose(m_window.GetHandle()))
	{
		glfwPollEvents();

		f32 time = (f32)glfwGetTime();
		f32 dt = time - m_lastFrameTime;
		m_lastFrameTime = time;
		Time::Get()->SetDeltaTime(dt);
		Time::Tick();


		m_isOpen = !glfwWindowShouldClose(m_window.GetHandle());
		m_window.Tick();

		m_appConfig.width = m_window.GetWindowConfig().width;
		m_appConfig.height = m_window.GetWindowConfig().height;
#if JIN_IMGUI
		NewFrameJinImGui();
#endif // JIN_NO_IMGUI

		for (auto layer : m_layers)
		{
			layer.second->Update();
		}


#if JIN_IMGUI
		RenderJinImGui();
#endif // JIN_NO_IMGUI

		auto renderTargetView = DX11::GetRenderTarget();
		float clearColor[4] = {1,0,0,1};
		DX11::GetContext()->OMSetRenderTargets(1, &renderTargetView, nullptr);
		DX11::GetContext()->ClearRenderTargetView(DX11::GetRenderTarget(), clearColor);


#if JIN_IMGUI
		RenderDrawDataJinImGui();
#endif // JIN_NO_IMGUI


		switch (m_appConfig.api)
		{
		case GraphicsAPI::DX11:
			DX11::GetSwaChain()->Present(0, 0);
			break;
		case GraphicsAPI::OpenGL:
			glfwSwapBuffers(m_window.GetHandle());
			break;
		default:
			break;
		}
	}

	for (auto layer : m_layers)
	{
		layer.second->End();
	}

	return true;
}

void Application::AddLayer(Layer* layer)
{
	m_layers.insert(std::pair<cstr, Layer*>(layer->GetName(), layer));
}

void Application::RemoveLayer(Layer* layer)
{
	m_layers.erase(layer->GetName());
}

bool Application::InitGLEW()
{
	if (glewInit() != GLEW_OK)
		return false;
	return true;
}

bool Application::InitGLFW()
{
	if (glfwInit() != GLFW_TRUE)
		return false;
	return true;
}
