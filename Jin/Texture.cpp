#include "Texture.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(void* data)
{
	GLenum internalFormat = GL_RGBA8, dataFormat = GL_RGBA;
	
	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTextureStorage2D(m_Id, 1, internalFormat, 1, 1);

	glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_Id, 0, 0, 0, 1, 1, dataFormat, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(cstr filePath, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	stbi_uc* data = stbi_load(filePath, &m_width, &m_height, &m_channels, 0);
	
	if (!data)
	{
		printf("Failed to open file : %s\n", filePath);
	}

	GLenum internalFormat = 0, dataFormat = 0;
	if (m_channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (m_channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	glGenTextures(1, &m_Id);
	glBindTexture(GL_TEXTURE_2D, m_Id);
	glTextureStorage2D(m_Id, 1, internalFormat, m_width, m_height);

	glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_Id, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	m_textureRect = {0,0, (f32)m_width, (f32)m_height};
}

void Texture::Bind(u32 slot) const 
{
	if (!m_bound)
	{
		m_bound = true;
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_Id);
	}
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
