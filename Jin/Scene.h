#pragma once
#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Window.h"
#include "Camera.h"
#include "Light.h"
#include <vector>
#include <algorithm>

class Scene
{
private:
	Camera* m_camera;
	std::vector<Light*> m_lights;

public:

	void SetCamera(Camera* cam) { m_camera = cam; }
	Camera* GetCamera() { return m_camera; }

	void AddLight(Light* light) { m_lights.push_back(light); }
	//void RemoveLight(Light light) { m_lights.erase(std::remove(m_lights.begin(), m_lights.end(), light), m_lights.end()); }

	std::vector<Light*> GetLights() { return m_lights; }

	void Update(const Window& window);
};