#include "Application.h"
#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include "Renderer.h"

Application::Application()
{
}

Application::~Application()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

static void window_size_callback(GLFWwindow* window, int width, int height)
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


	return true;
}

bool Application::Run()
{
	glfwSwapInterval(m_appConfig.vsync ? 1 : 0);
	return true;
}

bool Application::IsOpen()
{
	return m_isOpen;
}


void Application::Tick()
{
	m_isOpen = !glfwWindowShouldClose(m_window.GetHandle());
	m_window.Tick();

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

}


void Application::SwapBuffers()
{
	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(m_window.GetHandle());
}


void Application::PollEvents()
{
	glfwPollEvents();
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
