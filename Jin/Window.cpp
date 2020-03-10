#include "Window.h"
#include "Input.h"

Window::Window()
{
}

bool Window::Init(const WindowConfig& config)
{
	m_windowConfig = config;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_windowHandle = glfwCreateWindow(m_windowConfig.width, m_windowConfig.height, m_windowConfig.title, 0, 0);
	if (!m_windowHandle) return false;

	glfwMakeContextCurrent(m_windowHandle);

	return true;
}

void Window::Tick()
{
	glfwGetWindowSize(m_windowHandle, &m_windowConfig.width, &m_windowConfig.height);
}
