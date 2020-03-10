#pragma once
#include "Defines.h"
#include "Types.h"
#include <glm/glm.hpp>

enum class CameraType
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
	f32 m_rotation;
	f32 m_rotationSpeed;
	f32 m_translationSpeed;
	f32 m_width, m_height, m_far, m_near, m_fov;

public:
	Camera(f32 w, f32 h, f32 n, f32 f, f32 fov)
	{
		m_width = w;
		m_height = h;
		m_near = n;
		m_far = f;
		m_fov = fov;
	}

	virtual void Tick() = 0;
	JIN_INLINE CameraType GetType() { return m_type; }
	JIN_INLINE f32 GetFar() { return m_far; }
	JIN_INLINE f32 GetNear() { return m_near; }
	JIN_INLINE f32 GetFOV() { return m_fov; }

	JIN_INLINE void SetProjectionMatrix(const glm::mat4& proj) { m_projectionMatrix = proj; }
	JIN_INLINE glm::mat4& GetViewProjectionMatrix() { return m_viewProjectionMatrix; }
};

