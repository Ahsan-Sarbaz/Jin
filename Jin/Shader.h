#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

enum class ShaderType
{
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER,
	Geometry = GL_GEOMETRY_SHADER
};

class Shader
{
private:
	int m_ID;
	std::unordered_map<const char*, int> m_uniformCache;
	bool m_bound;
public:
	Shader(const char* vspath, const char* fspath);

	void Bind();
	void Unbind();

	int GetUniformLocation(const char* name);

	void SetUniformInt(const char* name, int val);
	void SetUniformFloat(const char* name, float x);
	void SetUniformFloat(const char* name, float x, float y);
	void SetUniformFloat(const char* name, float x, float y, float z);
	void SetUniformFloat(const char* name, float x, float y, float z, float w);
	void SetUniformVec2(const char* name, const glm::vec2& x);
	void SetUniformVec3(const char* name, const glm::vec3& x);
	void SetUniformVec4(const char* name, const glm::vec4& x);
	void SetUniformMat2(const char* name, const glm::mat2& x);
	void SetUniformMat3(const char* name, const glm::mat3& x);
	void SetUniformMat4(const char* name, const glm::mat4& x);

private:
	inline const std::string ReadShaderFile(const char* path);
	inline int CompileShader(const char* source, ShaderType Type);
};