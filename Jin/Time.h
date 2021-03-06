#pragma once
#include "pch.h"

class Time
{
    private:
	f32 m_Time = 0.0f;
	f32 dt = 0.0f;
	static Time* m_instance;
    
    
    public:
	Time(f32 time = 0.0f)
		: m_Time(time)
	{
		m_instance = this;
	}
    
	JIN_INLINE static Time* Get() { return m_instance; }
	JIN_INLINE static void Tick(f32 _dt) { m_instance->dt = _dt; m_instance->m_Time += m_instance->dt; }
    
	JIN_INLINE static f32 GetDeltaTime() { return m_instance->dt; }
	JIN_INLINE static f32 GetDeltaTimeMilliSeconds() { return m_instance->dt * 1000.0f; }
	JIN_INLINE static f32 GetSeconds() { return m_instance->m_Time; }
	JIN_INLINE static f32 GetMilliseconds() { return m_instance->m_Time * 1000.0f; }
	JIN_INLINE static void ResetTime() { m_instance->m_Time = 0.0f; }
	JIN_INLINE static f32 GetTimePulse(f32 time) { return fmod(m_instance->m_Time * 1000, time); }
};
