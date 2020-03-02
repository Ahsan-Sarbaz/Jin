#include "BatchRenderer2D.h"
#include <GL/glew.h>
#include <glm/ext/matrix_transform.hpp>

#define MAX_QUAD_COUNT 10000
#define MAX_VERT_COUNT MAX_QUAD_COUNT * 4
#define MAX_IND_COUNT MAX_QUAD_COUNT * 6

static RendererState state = {};

void BatchRenderer2D::Init()
{
	if (state.Initiated)
	{
		return;
	}

	state.Initiated = true;

	state.CurrentShader = new Shader("shaders/batchvs.glsl", "shaders/batchfs.glsl");

	glGenVertexArrays(1, &state.VAO);

	glGenBuffers(1, &state.VBO);
	glGenBuffers(1, &state.IBO);

	glBindVertexArray(state.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, state.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_VERT_COUNT, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_INT, false, sizeof(Vertex), (void*)offsetof(Vertex, texture));


	unsigned int* indices = new unsigned int[MAX_IND_COUNT];
	unsigned int offset = 0;
	for (size_t i = 0; i < MAX_IND_COUNT; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * MAX_IND_COUNT, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	delete[] indices;

	state.Buffer = new Vertex[MAX_VERT_COUNT];

	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &state.MaxTextureUnits);
	state.WhiteTexture = Texture(1, 1, 0xffffff);

	state.WhiteTexture.SetSlot(0);

	glUseProgram(state.CurrentShader->GetID());
	auto  location = glGetUniformLocation(state.CurrentShader->GetID(), "u_textures");
	int* samplers = new int[state.MaxTextureUnits];
	for (int i = 0; i < state.MaxTextureUnits; ++i)
	{
		samplers[i] = i;
	}
	glUniform1iv(location, state.MaxTextureUnits, samplers);
	delete[] samplers;
	state.CurrentShader->Unbind();
}

void BatchRenderer2D::Shutdown()
{
	delete state.CurrentShader;
	delete[] state.Buffer;
}

void BatchRenderer2D::Begin()
{
	state.BufferPtr = state.Buffer;
}

void BatchRenderer2D::End()
{
	GLsizeiptr size = (unsigned char*)state.BufferPtr - (unsigned char*)state.Buffer;
	glBindBuffer(GL_ARRAY_BUFFER, state.VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, state.Buffer);
}

void BatchRenderer2D::Flush()
{
	glBindVertexArray(state.VAO);
	glDrawElements(GL_TRIANGLES, state.IndexCount, GL_UNSIGNED_INT, nullptr);
	state.IndexCount = 0;
	state.DrawCount++;
}

void BatchRenderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
	if (state.IndexCount >= MAX_IND_COUNT)
	{
		End();
		Flush();
		Begin();
	}

	state.WhiteTexture.Bind();

	state.BufferPtr->position = { pos.x, pos.y, 0.0f };
	state.BufferPtr->color= color;
	state.BufferPtr->texCoord = { 0.0f, 0.0f };
	state.BufferPtr->texture = 0.0f;
	state.BufferPtr++;

	state.BufferPtr->position = { pos.x + size.x, pos.y, 0.0f };
	state.BufferPtr->color = color;
	state.BufferPtr->texCoord = { 1.0f, 0.0f };
	state.BufferPtr->texture = 0.0f;
	state.BufferPtr++;

	state.BufferPtr->position = { pos.x + size.x, pos.y + size.y, 0.0f };
	state.BufferPtr->color = color;
	state.BufferPtr->texCoord = { 1.0f, 1.0f };
	state.BufferPtr->texture = 0.0f;
	state.BufferPtr++;

	state.BufferPtr->position = { pos.x, pos.y + size.y, 0.0f };
	state.BufferPtr->color = color;
	state.BufferPtr->texCoord = { 0.0f, 1.0f };
	state.BufferPtr->texture = 0.0f;
	state.BufferPtr++;

	state.IndexCount += 6;

	state.QuadCount++;
}

void BatchRenderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Texture& texture)
{
	if (state.IndexCount >= MAX_IND_COUNT || state.TextureUnit >= state.MaxTextureUnits)
	{
		End();
		Flush();
		Begin();
		state.TextureUnit = 0;
	}

	glm::vec4 color = {1,1,1,1};
	int textureSlot = 0;
	if (state.TextureUnitCache.find(texture.GetID()) == state.TextureUnitCache.end())
	{
		//not found
		state.TextureUnitCache[texture.GetID()] = state.TextureUnit;
		textureSlot = state.TextureUnit;
		state.TextureUnit++;
	}
	else
	{
		textureSlot = state.TextureUnitCache[texture.GetID()];
		state.TextureUnit++;
	}

	texture.Bind(textureSlot);

	state.BufferPtr->position = { pos.x, pos.y, 0.0f };
	state.BufferPtr->color = color;
	state.BufferPtr->texCoord = { 0.0f, 0.0f };
	state.BufferPtr->texture = textureSlot;
	state.BufferPtr++;

	state.BufferPtr->position = { pos.x + size.x, pos.y, 0.0f };
	state.BufferPtr->color = color;
	state.BufferPtr->texCoord = { 1.0f, 0.0f };
	state.BufferPtr->texture = textureSlot;
	state.BufferPtr++;

	state.BufferPtr->position = { pos.x + size.x, pos.y + size.y, 0.0f };
	state.BufferPtr->color = color;
	state.BufferPtr->texCoord = { 1.0f, 1.0f };
	state.BufferPtr->texture = textureSlot;
	state.BufferPtr++;

	state.BufferPtr->position = { pos.x, pos.y + size.y, 0.0f };
	state.BufferPtr->color = color;
	state.BufferPtr->texCoord = { 0.0f, 1.0f };
	state.BufferPtr->texture = textureSlot;
	state.BufferPtr++;

	state.IndexCount += 6;

	state.QuadCount++;
}

const unsigned int BatchRenderer2D::GetDrawCount()
{
	return state.DrawCount;
}

const unsigned int BatchRenderer2D::GetQuadCount()
{
	return state.QuadCount;
}

Shader* BatchRenderer2D::GetShader()
{
	return state.CurrentShader;
}

void BatchRenderer2D::SetShader(Shader* shader)
{
	state.CurrentShader = shader;
}

void BatchRenderer2D::ResetStates()
{
	state.DrawCount = 0;
	state.QuadCount = 0;
}
