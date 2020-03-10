#pragma once
#include "Types.h"
#include "Defines.h"
#include "Maths.h"

class Texture
{
private:
	u32 m_Id;
	mutable bool m_bound =  false;
	mutable u32 m_slot = 0;
	i32 m_width;
	i32 m_height;
	i32 m_channels;
	Rect m_textureRect = {0,0,1,1};

public:
	Texture()
	{
		m_Id = 0;
	}

	Texture(void* data);
	Texture(cstr filePath, bool flip = 1);

	void Bind(u32 slot = 0) const;
	void Unbind();

	JIN_INLINE u32 GetID() const { return m_Id; }
	JIN_INLINE u32 GetSlot() const { return m_slot; }
	JIN_INLINE void SetSlot(u32 slot) const { m_slot = slot; }
	JIN_INLINE i32 GetWidth() const { return m_width; }
	JIN_INLINE i32 GetHeight() const { return m_height; }
	JIN_INLINE i32 GetChannels() const { return m_channels; }
	JIN_INLINE const Rect GetTextureRect() const { return m_textureRect; }
};