#pragma once
#include "Defines.h"
#include "Types.h"
#include "Texture.h"
#include <map>
#include "Maths.h"


class SpriteSheet
{
private:
	Texture* m_texture;
	f32 m_texWidth;
	f32 m_texHeight;
	f32 m_cellWidth;
	f32 m_cellHeight;
	std::map<u32, Rect> m_rects;

public:
	SpriteSheet();
	SpriteSheet(Texture* t, f32 cellW, f32 cellH);

	JIN_INLINE const Rect& GetSpriteRect(u32 id) const { return m_rects.find(id)->second; }
	JIN_INLINE const Texture* GetTexture() const { return m_texture; };
	JIN_INLINE const f32 GetTextureWidth() const { return m_texWidth; };
	JIN_INLINE const f32 GetTextureHeight() const { return m_texHeight; };
	JIN_INLINE const f32 GetCellWidth() const { return m_cellWidth; };
	JIN_INLINE const f32 GetCellHeight() const { return m_cellHeight; };
	JIN_INLINE const std::map<u32, Rect> GetCellRects() const { return m_rects; }
};

