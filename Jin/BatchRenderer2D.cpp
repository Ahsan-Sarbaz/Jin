#include "BatchRenderer2D.h"
#include <GL/glew.h>

#define MAX_QUAD_COUNT 10000
#define MAX_VERT_COUNT MAX_QUAD_COUNT * 4
#define MAX_IND_COUNT MAX_QUAD_COUNT * 6

BatchRenderer2D::BatchRenderer2D()
{
	glGenVertexArrays(1, &m_vao);

	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);

	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_VERT_COUNT, nullptr, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position));
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
	
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texture));


	unsigned int* indices = new unsigned int[MAX_IND_COUNT];
	unsigned int offset = 0;
	for (size_t i = 0; i < MAX_IND_COUNT; i+=6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * MAX_IND_COUNT, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	m_memory = new Vertex[MAX_VERT_COUNT];

}

BatchRenderer2D::~BatchRenderer2D()
{
}

void BatchRenderer2D::Begin()
{
	m_memoryPtr = m_memory;
}

void BatchRenderer2D::End()
{
	GLsizeiptr size = (unsigned char*)m_memoryPtr - (unsigned char*)m_memory;
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_memory);
}

void BatchRenderer2D::Flush()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
	m_indexCount = 0;
	m_DrawCount++;
}

void BatchRenderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
	if (m_indexCount >= MAX_IND_COUNT)
	{
		End();
		Flush();
		Begin();
	}

	m_memoryPtr->position = { pos.x, pos.y, 0.0f };
	m_memoryPtr->color= color;
	m_memoryPtr->texCoord = { 0.0f, 0.0f };
	m_memoryPtr->texture = 0;
	m_memoryPtr++;

	m_memoryPtr->position = { pos.x + size.x, pos.y, 0.0f };
	m_memoryPtr->color = color;
	m_memoryPtr->texCoord = { 1.0f, 0.0f };
	m_memoryPtr->texture = 0;
	m_memoryPtr++;

	m_memoryPtr->position = { pos.x + size.x, pos.y + size.y, 0.0f };
	m_memoryPtr->color = color;
	m_memoryPtr->texCoord = { 1.0f, 1.0f };
	m_memoryPtr->texture = 0;
	m_memoryPtr++;

	m_memoryPtr->position = { pos.x, pos.y + size.y, 0.0f };
	m_memoryPtr->color = color;
	m_memoryPtr->texCoord = { 0.0f, 1.0f };
	m_memoryPtr->texture = 0;
	m_memoryPtr++;

	m_indexCount += 6;

	m_QuadCount++;
}

void BatchRenderer2D::ResetStates()
{
	m_DrawCount = 0;
	m_QuadCount = 0;
}
