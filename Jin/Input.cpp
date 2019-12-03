#include "Input.h"

Input* Input::m_instance = nullptr;
bool Input::m_keyDown[] = {};
bool Input::m_keyRepeat[] = {};

Input::Input()
{
	m_instance = this;
}

bool Input::IsKeyDown(JinKey key)
{
	return m_keyDown[key];
}

bool Input::IsKeyUp(JinKey key)
{
	return !m_keyDown[key];
}

bool Input::IsKeyRepeat(JinKey key)
{
	return m_keyRepeat[key];
}
