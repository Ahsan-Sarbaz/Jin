#include "SpriteSheet.h"
#include "Application.h"

SpriteSheet::SpriteSheet()
{
}

SpriteSheet::SpriteSheet(Texture* t, f32 cellW, f32 cellH)
	:m_texture(t), m_cellWidth(cellW), m_cellHeight(cellH)
{
	if (Application::GetConfig().api != GraphicsAPI::OpenGL)
		return;

	m_texWidth = m_texture->GetWidth();
	m_texHeight = m_texture->GetHeight();

	f32 tw = m_cellWidth / m_texWidth;
	f32 th = m_cellHeight / m_texHeight;
	u32 numberPerRow = m_texWidth/ m_cellWidth;
	u32 numberPerCol = m_texHeight/ m_cellHeight;

	i32 id = 0;

	for (u32 y = 0; y < numberPerCol; y++)
	{
		for (u32 x = 0; x < numberPerRow; x++)
		{
			Rect r = { x * tw,
				y * th,
				(x * tw) + tw,
				(y * th) + th
			};

			m_rects.emplace(std::pair<u32, Rect>(id, r));
			id++;
		}
	}
}
