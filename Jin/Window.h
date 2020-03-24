#pragma once
#include "Defines.h"
#include "Types.h"
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

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
	HWND m_windowHandleWin32;

public:
	Window();

	bool Init(const WindowConfig& config);
	void Tick();

	JIN_INLINE GLFWwindow* GetHandle() const { return m_windowHandle; }
	JIN_INLINE HWND GetHandleWin32() const { return m_windowHandleWin32; }
	JIN_INLINE const WindowConfig& GetWindowConfig() const { return m_windowConfig; }
};