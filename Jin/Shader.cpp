#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>

Shader::Shader(const char* vspath, const char* fspath)
{
	std::string vsString = ReadShaderFile(vspath);
	std::string fsString = ReadShaderFile(fspath);

	auto vsSource = vsString.c_str();
	auto fsSource = fsString.c_str();

	int vsId = CompileShader(vsSource, ShaderType::Vertex);
	int fsId = CompileShader(fsSource, ShaderType::Fragment);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vsId);
	glAttachShader(m_ID, fsId);

	glLinkProgram(m_ID);
}

std::string Shader::ReadShaderFile(const char* path)
{
	std::ifstream file(path);
	std::stringstream ss;
	ss << file.rdbuf();
	std::string temp = ss.str();
	return temp;
}

int Shader::CompileShader(const char* source, ShaderType type)
{
	int shader = glCreateShader(type);
	
	glShaderSource(shader, 1, &source, 0);
	
	glCompileShader(shader);

	return shader;
}

