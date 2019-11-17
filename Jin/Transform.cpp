#include "Transform.h"

Transform::Transform()
{
	m_position = glm::vec3(0.0f);
	m_rotation = glm::vec3(0.0f);
	m_scale = glm::vec3(1.0f);
}

void Transform::UpdateMatrix()
{
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), { 1.0f, 0.0f, 0.0f }) 
		* glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), { 0.0f, 1.0f, 0.0f }) 
		* glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), { 0.0f, 0.0f, 1.0f });
	m_transform = glm::translate(glm::mat4(1.0f), m_position) * rot * glm::scale(glm::mat4(1.0f), m_scale);
}
