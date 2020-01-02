#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

class Material
{
private:
	glm::vec4 m_diffuse = glm::vec4(1,1,1,1);
	Texture* m_texture = new Texture();

public:
	Material();

	const glm::vec4& GetDiffuse() const { return m_diffuse; }
	glm::vec4& GetDiffuse() { return m_diffuse; }
	void SetDiffuse(const glm::vec4 diffuse) { m_diffuse = diffuse; }

	const Texture& GetTexture() const { return *m_texture; }
	Texture& GetTexture() { return *m_texture; }
	const void SetTexture(const Texture& texture) const { *m_texture = texture; }

	const bool HasTexture() const { return m_texture->GetID(); }
};

