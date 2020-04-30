#pragma once
#include "pch.h"

class Light
{
	glm::vec3 m_LightPosition;
	glm::vec3 m_LightColor;
    public:
	Light();
    
	void SetLightPosition(const glm::vec3& lightPos) { m_LightPosition = lightPos; }
	const glm::vec3& GetLightPosition() { return m_LightPosition; }
	glm::vec3& GetLightPositionRef() { return m_LightPosition; }
	
	void SetLightColor(const glm::vec3& lightCol) { m_LightColor = lightCol; }
	const glm::vec3& GetLightColor() { return m_LightColor; }
	glm::vec3& GetLightColorRef() { return m_LightColor; }
};

