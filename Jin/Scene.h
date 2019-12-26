#pragma once
#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Window.h"
#include "Camera.h"

class Scene
{
private:
	Camera* m_camera;

public:

	void SetCamera(Camera* cam) { m_camera = cam; }
	Camera* GetCamera() { return m_camera; }

	void Update(const Window& window);
};