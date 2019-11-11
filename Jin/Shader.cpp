#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

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

	int success;
	char infoLog[512];
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vsId);
	glDeleteShader(fsId);
}

void Shader::Bind()
{
	glUseProgram(m_ID);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

const std::string Shader::ReadShaderFile(const char* path)
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
	
	glShaderSource(shader, 1, &source,  0);
	
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION\n" << infoLog << std::endl;
	}

	return shader;
}

int Shader::GetUniformLocation(const char* name)
{
	if (m_uniformCache.find(name) != m_uniformCache.end())
	{
		m_uniformCache[name] = glGetUniformLocation(m_ID, name);
	}

	return m_uniformCache[name];
}

void Shader::SetUniformInt(const char* name, int val)
{
	glUniform1i(GetUniformLocation(name), val);
}

void Shader::SetUniformFloat(const char* name, float x)
{
	glUniform1f(GetUniformLocation(name), x);
}

void Shader::SetUniformFloat(const char* name, float x, float y)
{
	glUniform2f(GetUniformLocation(name), x, y);
}

void Shader::SetUniformFloat(const char* name, float x, float y, float z)
{
	glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetUniformFloat(const char* name, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetUniformVec2(const char* name, const glm::vec2& x)
{
	glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(x));
}

void Shader::SetUniformVec3(const char* name, const glm::vec3& x)
{
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(x));
}

void Shader::SetUniformVec4(const char* name, const glm::vec4& x)
{
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(x));
}

void Shader::SetUniformMat2(const char* name, const glm::mat2& x)
{
	glUniformMatrix2fv(GetUniformLocation(name), 1, false, glm::value_ptr(x));
}

void Shader::SetUniformMat3(const char* name, const glm::mat3& x)
{
	glUniformMatrix2fv(GetUniformLocation(name), 1, false, glm::value_ptr(x));
}

void Shader::SetUniformMat4(const char* name, const glm::mat4& x)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(x));
}

