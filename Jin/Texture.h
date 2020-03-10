#pragma once
#include "Types.h"
#include "Defines.h"

class Texture
{
private:
	u32 m_Id;
	mutable bool m_bound =  false;
	mutable u32 m_slot = 0;

public:
	Texture()
	{
		m_Id = 0;
	}

	Texture(u32 width, u32 height, u8 color);
	Texture(cstr filePath, bool flip = 1);

	void Bind(u32 slot = 0) const;
	void Unbind();

	JIN_INLINE u32 GetID() const { return m_Id; }
	JIN_INLINE u32 GetSlot() const { return m_slot; }
	JIN_INLINE void SetSlot(u32 slot) const { m_slot = slot; }

};