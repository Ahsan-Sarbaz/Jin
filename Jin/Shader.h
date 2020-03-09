#pragma once
#include "Types.h"
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include "Maths.h"

enum class ShaderType
{
	Vertex = GL_VERTEX_SHADER,
	Fragment = GL_FRAGMENT_SHADER,
	Geometry = GL_GEOMETRY_SHADER
};

class Shader
{
private:
	i32 m_ID;
	std::unordered_map<cstr, i32> m_uniformCache;
	bool m_bound;
public:
	Shader(cstr vspath, cstr fspath);

	void Bind();
	void Unbind();

	i32 GetID() { return m_ID; }

	i32 GetUniformLocation(const char* name);

	void SetUniformInt(cstr name, int val);
	void SetUniformFloat(cstr name, float x);
	void SetUniformFloat(cstr name, float x, float y);
	void SetUniformFloat(cstr name, float x, float y, float z);
	void SetUniformFloat(cstr name, float x, float y, float z, float w);
	void SetUniformVec2(cstr name, const Vec2& x);
	void SetUniformVec3(cstr name, const Vec3& x);
	void SetUniformVec4(cstr name, const Vec4& x);
	void SetUniformMat2(cstr name, const glm::mat2& x);
	void SetUniformMat3(cstr name, const glm::mat3& x);
	void SetUniformMat4(cstr name, const glm::mat4& x);

private:
	const std::string ReadShaderFile(cstr path);
	i32 CompileShader(cstr source, ShaderType Type);
};