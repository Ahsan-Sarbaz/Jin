#pragma once
#include "Defines.h"
#include "Types.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
enum class IMGUIGraphicsAPI
{
	DX11,
	OpenGL
};

enum class GraphicsAPI;

struct JinIMGUIState
{
	GLFWwindow* windowGLFW;
	HWND windowWin32;
	IMGUIGraphicsAPI api;
};

static JinIMGUIState jin_imgui_state = {};

JIN_INLINE void InitJinImgui(IMGUIGraphicsAPI api, ID3D11Device* device, ID3D11DeviceContext* context, GLFWwindow* window, HWND windowWin32)
{

	jin_imgui_state.api = api;
	jin_imgui_state.windowGLFW = window;
	jin_imgui_state.windowWin32 = windowWin32;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	switch (api)
	{
	case IMGUIGraphicsAPI::DX11:
		ImGui_ImplWin32_Init(windowWin32);
		ImGui_ImplDX11_Init(device, context);
		break;
	case IMGUIGraphicsAPI::OpenGL:
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
		break;
	default:
		break;
	}
}

JIN_INLINE void ShutdownJinImGui()
{
	switch (jin_imgui_state.api)
	{
	case IMGUIGraphicsAPI::DX11:
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		break;
	case IMGUIGraphicsAPI::OpenGL:
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		break;
	default:
		break;
	}

	ImGui::DestroyContext();
}

JIN_INLINE void NewFrameJinImGui()
{
	switch (jin_imgui_state.api)
	{
	case IMGUIGraphicsAPI::DX11:
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		break;
	case IMGUIGraphicsAPI::OpenGL:
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		break;
	default:
		break;
	}

	ImGui::NewFrame();

}

JIN_INLINE void RenderDrawDataJinImGui()
{
	switch (jin_imgui_state.api)
	{
	case IMGUIGraphicsAPI::DX11:
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		break;
	case IMGUIGraphicsAPI::OpenGL:
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		break;
	default:
		break;
	}
}

JIN_INLINE void RenderJinImGui()
{
	ImGui::Render();
}







