#pragma once

class Time
{
private:
	float m_Time = 0.0f;
	float dt = 0.0f;
	static Time* m_instance;


public:
	Time(float time = 0.0f)
		: m_Time(time)
	{
		m_instance = this;
	}

	static Time* Get() { return m_instance; }

	void SetDeltaTime(float _dt) { m_instance->dt = _dt; }

	static float GetDeltaTime() { return m_instance->dt; }
	static float GetDeltaTimeMilliSeconds() { return m_instance->dt * 1000.0f; }
	static float GetSeconds() { return m_instance->m_Time; }
	static float GetMilliseconds() { return m_instance->m_Time * 1000.0f; }

};
