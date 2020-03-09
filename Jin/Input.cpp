#include "Application.h"
#include "Input.h"

float Input::GetMouseX()
{
	auto window = Application::Get()->GetWindow().GetHandle();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return (float)xpos;
}

float Input::GetMouseY()
{
	auto window = Application::Get()->GetWindow().GetHandle();
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	return (float)ypos;
}

bool Input::IsKeyPressed(JinKey key)
{
	auto window = Application::Get()->GetWindow().GetHandle();
	auto state = glfwGetKey(window, key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(JinMouseButton button)
{	
	auto window = Application::Get()->GetWindow().GetHandle();
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

