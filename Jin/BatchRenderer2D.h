#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include <unordered_map>
#include "Shader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoord;
	unsigned int texture;
};

class BatchRenderer2D
{
private:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;
	Vertex* m_memory;
	Vertex* m_memoryPtr = nullptr;
	unsigned int m_indexCount = 0;
	unsigned int m_QuadCount = 0;
	unsigned int m_DrawCount = 0;
	int m_MaxtextureSlot = 0;
	int m_textureSlot = 1;
	Texture m_whiteTexture;
	std::unordered_map<int, int> m_textureIDSlotCache;
	Shader* m_shader;

public:
	BatchRenderer2D();
	~BatchRenderer2D();

	void Begin();
	void End();
	void Flush();

	void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
	void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Texture& texture);

	const unsigned int GetDrawCount() const { return m_DrawCount; }
	const unsigned int GetQuadCount() const { return m_QuadCount; }

	Shader* GetShader() { return m_shader; }
	void SetShader(Shader* shader) { m_shader = shader; }

	void ResetStates();
};