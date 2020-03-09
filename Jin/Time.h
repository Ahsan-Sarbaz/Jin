#pragma once
#include "Types.h"
#include "Defines.h"

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

	JIN_INLINE void SetDeltaTime(float _dt) { m_instance->dt = _dt; }

	JIN_INLINE static f32 GetDeltaTime() { return m_instance->dt; }
	JIN_INLINE static f32 GetDeltaTimeMilliSeconds() { return m_instance->dt * 1000.0f; }
	JIN_INLINE static f32 GetSeconds() { return m_instance->m_Time; }
	JIN_INLINE static f32 GetMilliseconds() { return m_instance->m_Time * 1000.0f; }

};
