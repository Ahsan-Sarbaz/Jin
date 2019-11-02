#pragma once
#include <GL/glew.h>
#include <string>

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
public:
	Shader(const char* vspath, const char* fspath);

private:
	std::string ReadShaderFile(const char* path);
	int CompileShader(const char* source, ShaderType Type);
};