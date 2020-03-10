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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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
	
	if (!InitGLEW()) return false;

	m_isOpen = true;

	glfwSetWindowSizeCallback(m_window.GetHandle(), window_size_callback);

#if JIN_IMGUI
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_window.GetHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 130");
#endif // JIN_NO_IMGUI

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


		m_isOpen = !glfwWindowShouldClose(m_window.GetHandle());
		m_window.Tick();

		m_appConfig.width = m_window.GetWindowConfig().width;
		m_appConfig.height = m_window.GetWindowConfig().height;
#if JIN_IMGUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
#endif // JIN_NO_IMGUI

		for (auto layer : m_layers)
		{
			layer.second->Update();
		}

#if JIN_IMGUI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif // JIN_NO_IMGUI

		glfwSwapBuffers(m_window.GetHandle());
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
