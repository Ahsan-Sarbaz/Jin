#include "Renderer2D.h"
#include <glm/ext/matrix_transform.hpp>
#include "Shader.h"

Renderer2D::Renderer2D()
{

}

void Renderer2D::Init(RendererConfig& config)
{
	m_config = config;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	float verts[] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	
	unsigned int indices[] =
	{
		 0, 1, 2, 2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 5 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	m_shader = new Shader("shaders/vs.glsl", "shaders/fs.glsl");
	
}

void Renderer2D::BeginScene()
{
	m_shader->Bind();	
	m_shader->SetUniformMat4("u_Projection", m_config.projectionMatrix);
}

void Renderer2D::EndScene()
{
	m_shader->Unbind();
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
{
	m_shader->SetUniformVec4("u_Color", color);

	glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), size);
	m_shader->SetUniformMat4("u_Tranform", transformation);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec3& size, const Texture& texture)
{
	m_shader->SetUniformVec4("u_Color", {1,1,1,1});

	glm::mat4 transformation = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), size);
	m_shader->SetUniformMat4("u_Tranform", transformation);
	texture.Bind();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer2D::DrawQuad(const Transform& transform, const Texture& texture)
{
	m_shader->SetUniformVec4("u_Color", {1,1,1,1});

	m_shader->SetUniformMat4("u_Tranform", transform.GetTransform());
	texture.Bind();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


void Renderer2D::DrawQuad(const Transform& transform, const glm::vec4& color)
{
	m_shader->SetUniformVec4("u_Color", color);

	m_shader->SetUniformMat4("u_Tranform", transform.GetTransform());

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer2D::Clear(const glm::vec4& clearColor)
{
	m_clearColor = clearColor;
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
