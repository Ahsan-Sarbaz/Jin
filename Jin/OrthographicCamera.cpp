#include "OrthographicCamera.h"
#include "Input.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include "Time.h"

OrthographicCamera::OrthographicCamera(int width, int height)
	:Camera(width, height, -1.0f, 1.0f, 0)
{
	m_type = Orthographic;
	m_projectionMatrix = glm::orthoLH(0.0f, m_width, m_height, 0.0f, m_near, m_far);
	m_position = glm::vec3(0.0f);
	m_rotation = 0;
	m_rotationSpeed = 90.0f;
	m_translationSpeed = 1000.0f;
}

void OrthographicCamera::Tick()
{
	float dt = Time::GetDeltaTime();
	if (Input::IsKeyPressed(JinKey::LEFT) || Input::IsKeyPressed(JinKey::A))
	{
		m_position.x -= cos(glm::radians(m_rotation)) * m_translationSpeed * dt;
		m_position.y -= sin(glm::radians(m_rotation)) * m_translationSpeed * dt;
	}

	if (Input::IsKeyPressed(JinKey::RIGHT) || Input::IsKeyPressed(JinKey::D))
	{
		m_position.x+= cos(glm::radians(m_rotation)) * m_translationSpeed * dt;
		m_position.y+= sin(glm::radians(m_rotation)) * m_translationSpeed * dt;
	}

	if (Input::IsKeyPressed(JinKey::UP) || Input::IsKeyPressed(JinKey::W))
	{
		m_position.x += -sin(glm::radians(m_rotation)) * m_translationSpeed * dt;
		m_position.y += cos(glm::radians(m_rotation)) * m_translationSpeed * dt;
	}

	if (Input::IsKeyPressed(JinKey::DOWN) || Input::IsKeyPressed(JinKey::S))
	{
		m_position.x -= -sin(glm::radians(m_rotation)) * m_translationSpeed * dt;
		m_position.y -= cos(glm::radians(m_rotation)) * m_translationSpeed * dt;
	}

	if (Input::IsKeyPressed(JinKey::Q))
	{
		m_rotation += m_rotationSpeed * dt;
	}

	if (Input::IsKeyPressed(JinKey::E))
	{
		m_rotation -= m_rotationSpeed * dt;
	}
	
	if (m_rotation > 180.0f)
		m_rotation -= 360.0f;
	else if (m_rotation <= -180.0f)
		m_rotation += 360.0f;

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_position) *
		glm::rotate(glm::mat4(1.0f	), glm::radians(m_rotation), glm::vec3(0, 0, 1));
	m_viewMatrix = glm::inverse(transform);


	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}