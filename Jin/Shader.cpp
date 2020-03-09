#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(cstr vspath, cstr fspath)
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
	if (!m_bound)
	{
		glUseProgram(m_ID);
		m_bound = true;
	}
}

void Shader::Unbind()
{
	if (m_bound)
	{
		glUseProgram(0);
		m_bound = false;
	}
}

const std::string Shader::ReadShaderFile(cstr path)
{
	std::ifstream file(path);
	std::stringstream ss;
	ss << file.rdbuf();
	std::string temp = ss.str();
	return temp;
}

int Shader::CompileShader(cstr source, ShaderType type)
{
	GLenum shaderType = 0;

	switch (type)
	{
	case ShaderType::Vertex:
		shaderType = GL_VERTEX_SHADER;
		break;
	case ShaderType::Fragment:
		shaderType = GL_FRAGMENT_SHADER;
		break;
	case ShaderType::Geometry:
		shaderType = GL_GEOMETRY_SHADER;
		break;
	default:
		break;
	}

	int shader = glCreateShader(shaderType);
	
	glShaderSource(shader, 1, &source,  0);
	
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		if (type == ShaderType::Vertex)
		{
			std::cout << "ERROR::VERTEX_SHADER::PROGRAM::COMPILATION\n" << infoLog << std::endl;
		}
		else if (type == ShaderType::Fragment)
		{
			std::cout << "ERROR::FRAGMENT_SHADER::PROGRAM::COMPILATION\n" << infoLog << std::endl;
		}
	}

	return shader;
}

int Shader::GetUniformLocation(cstr name)
{
	if (m_uniformCache.find(name) != m_uniformCache.end())
	{
		m_uniformCache[name] = glGetUniformLocation(m_ID, name);
	}

	return m_uniformCache[name];
}

void Shader::SetUniformInt(cstr name, int val)
{
	glUniform1i(GetUniformLocation(name), val);
}

void Shader::SetUniformFloat(cstr name, float x)
{
	glUniform1f(GetUniformLocation(name), x);
}

void Shader::SetUniformFloat(cstr name, float x, float y)
{
	glUniform2f(GetUniformLocation(name), x, y);
}

void Shader::SetUniformFloat(cstr name, float x, float y, float z)
{
	glUniform3f(GetUniformLocation(name), x, y, z);
}
  
void Shader::SetUniformFloat(cstr name, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetUniformVec2(cstr name, const Vec2& x)
{
	glUniform2fv(GetUniformLocation(name), 1, x.data);
}

void Shader::SetUniformVec3(cstr name, const Vec3& x)
{
	glUniform3fv(GetUniformLocation(name), 1, x.data);
}

void Shader::SetUniformVec4(cstr name, const Vec4& x)
{
	glUniform4fv(GetUniformLocation(name), 1, x.data);
}

void Shader::SetUniformMat2(cstr name, const glm::mat2& x)
{
	glUniformMatrix2fv(GetUniformLocation(name), 1, false, glm::value_ptr(x));
}

void Shader::SetUniformMat3(cstr name, const glm::mat3& x)
{
	glUniformMatrix2fv(GetUniformLocation(name), 1, false, glm::value_ptr(x));
}

void Shader::SetUniformMat4(cstr name, const glm::mat4& x)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(x));
}

