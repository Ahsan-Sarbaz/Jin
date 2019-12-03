#pragma once


class Texture
{
private:
	unsigned int m_Id;
	mutable bool m_bound =  false;

public:
	Texture(const char* filePath);

	void Bind(unsigned int slot = 0) const;
	void Unbind();

	unsigned int GetID() const { return m_Id; }
};