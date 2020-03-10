#include "Texture.h"
#include <GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(u32 width, u32 height, u8 color)
{
	u8* data = (u8*)malloc(width * height * sizeof(u8));

	for (u32 i = 0; i < (width * height * sizeof(u8)); ++i)
	{
		data[i] = color;
	}

	GLenum internalFormat = GL_RGB8, dataFormat = GL_RGB;
	

	glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
	glTextureStorage2D(m_Id, 1, internalFormat, width, height);

	glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_Id, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);
}

Texture::Texture(cstr filePath, bool flip)
{
	i32 width, height, channels;
	stbi_set_flip_vertically_on_load(flip);
	stbi_uc* data = stbi_load(filePath, &width, &height, &channels, 0);
	
	if (!data)
	{
		printf("Failed to open file : %s\n", filePath);
	}

	GLenum internalFormat = 0, dataFormat = 0;
	if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	glCreateTextures(GL_TEXTURE_2D, 1, &m_Id);
	glTextureStorage2D(m_Id, 1, internalFormat, width, height);

	glTextureParameteri(m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(m_Id, 0, 0, 0, width, height, dataFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

void Texture::Bind(u32 slot) const 
{
	if (!m_bound)
	{
		m_bound = true;
		glBindTextureUnit(slot, m_Id);
	}
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
