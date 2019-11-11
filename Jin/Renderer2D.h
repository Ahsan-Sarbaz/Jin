#pragma once
#include "Renderer.h"
#include "Shader.h"
#include <glm/glm.hpp>

class Renderer2D :
	public Renderer
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
	Shader* m_shader;

public:
	Renderer2D();
	virtual void Init(RendererConfig& config) override;

	void DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
};

