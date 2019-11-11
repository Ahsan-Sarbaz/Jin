#pragma once
#include <glm/glm.hpp>

struct RendererConfig
{
	glm::mat4 projectionMatrix;
};

class Renderer
{
public:
	RendererConfig m_config;
	virtual void Init(RendererConfig& config) = 0;
};