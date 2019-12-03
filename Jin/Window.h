#pragma once
#include <GLFW/glfw3.h>

struct WindowConfig
{
	int width, height;
	const char* title;
};

class Window
{
private:
	WindowConfig m_windowConfig;
	GLFWwindow* m_windowHandle;

public:
	Window();

	bool Init(const WindowConfig& config);
	void Tick();

	inline GLFWwindow* GetHandle() const { return m_windowHandle; }
	const WindowConfig& GetWindowConfig() const { return m_windowConfig; }
};