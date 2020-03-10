#pragma once
#include "Types.h"
#include <GLFW/glfw3.h>

struct WindowConfig
{
	i32 width, height;
	cstr title;
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