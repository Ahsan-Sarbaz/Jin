#include "pch.h"
#include "PerspectiveCamera.h"
#include "Input.h"
#include "Time.h"

PerspectiveCamera::PerspectiveCamera(f32 width, f32 height, f32 near, f32 far, f32 fov)
:Camera(width, height, near, far, fov)
{
	m_type = CameraType::Perspective;
	m_projectionMatrix = glm::perspectiveLH(m_fov, m_width/m_height, m_near, m_far);
	m_position = glm::vec3(0.0f);
	m_rotation = 0;
	m_rotationSpeed = 90.0f;
	m_translationSpeed = 1000.0f;
}

void PerspectiveCamera::Tick()
{
	f32 dt = Time::GetDeltaTime();
	if (Input::IsKeyPressed(JinKey::KEY_LEFT) || Input::IsKeyPressed(JinKey::KEY_A))
	{
		m_position.x -= cos(glm::radians(m_rotation)) * m_translationSpeed * dt;
		m_position.y -= sin(glm::radians(m_rotation)) * m_translationSpeed * dt;
	}
    
	if (Input::IsKeyPressed(JinKey::KEY_RIGHT) || Input::IsKeyPressed(JinKey::KEY_D))
	{
		m_position.x += cos(glm::radians(m_rotation)) * m_translationSpeed * dt;
		m_position.y += sin(glm::radians(m_rotation)) * m_translationSpeed * dt;
	}
    
	if (Input::IsKeyPressed(JinKey::KEY_UP) || Input::IsKeyPressed(JinKey::KEY_W))
	{
		m_position.x += -sin(glm::radians(m_rotation)) * m_translationSpeed * dt;
		m_position.y += cos(glm::radians(m_rotation)) * m_translationSpeed * dt;
	}
    
	if (Input::IsKeyPressed(JinKey::KEY_DOWN) || Input::IsKeyPressed(JinKey::KEY_S))
	{
		m_position.x -= -sin(glm::radians(m_rotation)) * m_translationSpeed * dt;
		m_position.y -= cos(glm::radians(m_rotation)) * m_translationSpeed * dt;
	}
    
	if (Input::IsKeyPressed(JinKey::KEY_Q))
	{
		m_rotation += m_rotationSpeed * dt;
	}
    
	if (Input::IsKeyPressed(JinKey::KEY_E))
	{
		m_rotation -= m_rotationSpeed * dt;
	}
    
	if (m_rotation > 180.0f)
		m_rotation -= 360.0f;
	else if (m_rotation <= -180.0f)
		m_rotation += 360.0f;
    
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), glm::vec3(0, 0, 1));
	m_viewMatrix = glm::inverse(transform);
    
    
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}
