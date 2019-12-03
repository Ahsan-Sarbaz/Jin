#pragma once
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "Scene.h"

class Renderer2D :
	public Renderer
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ibo;
	Shader* m_shader;
	glm::vec4 m_clearColor;

public:
	Renderer2D();
	virtual void Init(RendererConfig& config) override;

	void BeginScene(Scene& s);
	void EndScene();
	void DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
	void DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, const Texture& texture);
	void DrawQuad(const glm::vec3& position, const glm::vec3& size, const Texture& texture);
	void DrawQuad(const Transform& transform, const glm::vec4& color, const Texture& texture);
	void DrawQuad(const Transform& transform, const Texture& texture);
	void DrawQuad(const Transform& transform, const glm::vec4& color);
	void Clear(const glm::vec4& clearColor);
};

