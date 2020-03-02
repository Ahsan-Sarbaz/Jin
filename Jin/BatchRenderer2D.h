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

struct RendererState
{
	bool Initiated = false;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int IBO;
	Vertex* Buffer;
	Vertex* BufferPtr = nullptr;
	unsigned int IndexCount = 0;
	unsigned int QuadCount = 0;
	unsigned int DrawCount = 0;
	int MaxTextureUnits = 0;
	int TextureUnit = 1;
	Texture WhiteTexture;
	std::unordered_map<int, int> TextureUnitCache;
	Shader* CurrentShader;
};

class BatchRenderer2D
{
public:
	
	static void Init();
	static void Shutdown();

	static void Begin();
	static void End();
	static void Flush();

	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Texture& texture);

	static const unsigned int GetDrawCount();
	static const unsigned int GetQuadCount();

	static Shader* GetShader();
	static void SetShader(Shader* shader);

	static void ResetStates();
};