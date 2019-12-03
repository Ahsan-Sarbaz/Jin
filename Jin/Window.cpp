#include "Window.h"
#include "Input.h"

Window::Window()
{
}

static void mouse_callback(GLFWwindow* window, double x, double y)
{
	Input::Get().SetMouseX(x);
	Input::Get().SetMouseY(y);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input::Get().SetKeyDown((JinKey)key, (action == GLFW_PRESS) ? true : false);
	Input::Get().SetKeyRepeat((JinKey)key, (action == GLFW_REPEAT) ? true : false);
}

bool Window::Init(const WindowConfig& config)
{
	m_windowConfig = config;

	m_windowHandle = glfwCreateWindow(m_windowConfig.width, m_windowConfig.height, m_windowConfig.title, 0, 0);
	if (!m_windowHandle) return false;

	glfwMakeContextCurrent(m_windowHandle);

	glfwSetCursorPosCallback(m_windowHandle, mouse_callback);
	glfwSetKeyCallback(m_windowHandle, key_callback);

	return true;
}