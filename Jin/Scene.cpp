#include "Scene.h"

void Scene::Update(const Window& window)
{
	float width = window.GetWindowConfig().width;
	float height = window.GetWindowConfig().height;
	float far = m_camera->GetFar();
	float near = m_camera->GetNear();
	float fov = m_camera->GetFOV();

	if (m_camera->GetType() == Perspective)
	{
		m_camera->SetProjectionMatrix(glm::perspectiveLH(fov, width/height, near, far));
	}
	else if (m_camera->GetType() == Orthographic)
	{
		m_camera->SetProjectionMatrix(glm::orthoLH(0.0f, width, height, 0.0f, near, far));
	}

	m_camera->Tick();
}
