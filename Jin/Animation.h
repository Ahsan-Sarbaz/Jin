#ifndef _ANIMATION_H
#define _ANIMATION_H
#include "pch.h"
#include "SpriteSheet.h"

class Animation
{
    private:
    SpriteSheet* m_sheet;
    float m_animAccum = 0;
    float m_animationTimeStep = 0;
    int m_index;
    int m_start;
    int m_end;
    float m_dt;
    float m_fps;
    float m_runningTime;
    
    public:
    Animation();
    Animation(SpriteSheet* sheet, int start, int end, float fps);
    
    void Update();
    void Draw(const Vec2& pos, const Vec2& size);
    JIN_INLINE SpriteSheet* GetSpriteSheet() { return m_sheet; }
};


#endif //_ANIMATION_H
