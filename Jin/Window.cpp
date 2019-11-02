#include "Window.h"

Window::Window()
{
}

bool Window::Init(const WindowConfig& config)
{
	m_windowConfig = config;

	m_windowHandle = glfwCreateWindow(m_windowConfig.width, m_windowConfig.height, m_windowConfig.title, 0, 0);
	if (!m_windowHandle) return false;

	glfwMakeContextCurrent(m_windowHandle);

	return true;
}