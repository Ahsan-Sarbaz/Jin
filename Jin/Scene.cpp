#include "Scene.h"

void Scene::Update(const Window& window)
{
	m_projection = glm::ortho(0.0f, (float)window.GetWindowConfig().width, (float)window.GetWindowConfig().height, 0.0f, -1.0f, 1.0f);
}
