#pragma once
#include <glm/glm.hpp>

enum CameraType
{
	Perspective,
	Orthographic
};

class Camera
{
protected:
	CameraType m_type;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_viewProjectionMatrix;
	glm::vec3 m_position;
	float m_rotation;
	float m_rotationSpeed;
	float m_translationSpeed;
	float m_width, m_height, m_far, m_near, m_fov;

public:
	Camera(float w, float h, float n, float f, float fov)
	{
		m_width = w;
		m_height = h;
		m_near = n;
		m_far = f;
		m_fov = fov;
	}

	virtual void Tick() = 0;
	CameraType GetType() { return m_type; }
	float GetFar() { return m_far; }
	float GetNear() { return m_near; }
	float GetFOV() { return m_fov; }

	void SetProjectionMatrix(const glm::mat4& proj) { m_projectionMatrix = proj; }
	glm::mat4& GetViewProjectionMatrix() { return m_viewProjectionMatrix; }
};

