#include "pch.h"
#include "Animation.h"
#include "BatchRenderer2D.h"
#include "Time.h"

Animation::Animation()
{
}

Animation::Animation(SpriteSheet* sheet, int start, int end, float runningTime)
:m_sheet(sheet), m_start(start), m_end(end), m_runningTime(runningTime)
{
    m_index = start;
    if(m_start >= m_sheet->GetCellCount())
        assert(0);
    if(m_end > m_sheet->GetCellCount() ||( m_end == 0))
        m_end = m_sheet->GetCellCount();
    
    
    m_fps = (m_end - m_start) / m_runningTime;
    m_animationTimeStep = 1.0f / m_fps;
}

void Animation::Update()
{
    m_dt = Time::GetDeltaTime();
    m_animAccum += m_dt;
    if(m_animAccum >= m_animationTimeStep)
    {
        m_index++;
        if(m_index >= m_end)
            m_index = m_start;
        m_animAccum = 0;
    }
}

void Animation::Draw(const Vec2& pos, const Vec2& size)
{
    BatchRenderer2D::DrawQuad(pos, size, *m_sheet, m_index);
}

