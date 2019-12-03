#pragma once
#include <glm/glm.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Window.h"

class Scene
{
private:
	glm::mat4 m_projection;
public:

	void SetProjection(const glm::mat4& proj) { m_projection = proj; }
	const glm::mat4& GetProjection() { return m_projection; }

	void Update(const Window& window);
};