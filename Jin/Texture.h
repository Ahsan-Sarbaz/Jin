#pragma once


class Texture
{
private:
	unsigned int m_Id;
	mutable bool m_bound =  false;
	mutable unsigned int m_slot = 0;

public:
	Texture()
	{
		m_Id = 0;
	}

	Texture(unsigned int width, unsigned int height, unsigned char color);
	Texture(const char* filePath);

	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline unsigned int GetID() const { return m_Id; }
	inline unsigned int GetSlot() const { return m_slot; }
	inline void SetSlot(unsigned int slot) const { m_slot = slot; }

};