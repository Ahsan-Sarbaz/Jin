#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>

enum ShaderType
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
public:
	Shader(const char* vspath, const char* fspath);

private:
	std::string ReadShaderFile(const char* path);
	int CompileShader(const char* source, ShaderType Type);

	int GetUniformLocation(const char* name);

	void SetUniformInt(const char* name, int val);
	void SetUniformFloat(const char* name, float x);
	void SetUniformFloat(const char* name, float x, float y);
	void SetUniformFloat(const char* name, float x, float y, float z);
	void SetUniformFloat(const char* name, float x, float y, float z, float w);
};