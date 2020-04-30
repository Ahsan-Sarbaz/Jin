#pragma once
#include "pch.h"

class Transform
{
    private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_transform;
    
    public:
	Transform();
    
	void UpdateMatrix();
    
	inline const glm::mat4& GetTransform() const { return m_transform; }
    
	inline const glm::vec3 GetPosition() const { return m_position; };
	inline const glm::vec3 GetRotation() const { return m_rotation; };
	inline const glm::vec3 GetScale() const { return m_scale; };
	
	inline const glm::vec3 SetPosition(const glm::vec3& position) { m_position = position; UpdateMatrix(); return m_position; };
	inline const glm::vec3 SetRotation(const glm::vec3& rotation) { m_rotation = rotation; UpdateMatrix(); return m_rotation; };
	inline const glm::vec3 SetScale(const glm::vec3& scale) { m_scale = scale; UpdateMatrix(); return m_scale; };
};