#include "Application.h"

Application::Application()
{
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

	return true;
}

bool Application::Run()
{
	return true;
}

bool Application::IsOpen()
{
	return m_isOpen;
}


void Application::Tick()
{
	m_isOpen = !glfwWindowShouldClose(m_window.GetHandle());
}

void Application::SwapBuffers()
{
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