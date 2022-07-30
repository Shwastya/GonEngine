#pragma once

class Event;

struct DeltaTime
{
	DeltaTime(float time = 0.0f) :m_Time(time) {}
	operator float() const { return m_Time; }
	const float Seconds() const { return m_Time; }
	const float MilliSeconds() const { return m_Time * 1000.0f; }
private:
	float m_Time;
};