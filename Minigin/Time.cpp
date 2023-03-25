#include "Time.h"

Time::Time()
{
	m_Start = std::chrono::high_resolution_clock::now();
}

void Time::Update()
{
	m_CurrentPoint = std::chrono::high_resolution_clock::now();

	m_DeltaTime = std::chrono::duration<float>(m_CurrentPoint - m_LastPoint).count();
	m_LastPoint = m_CurrentPoint;
}

void Time::SetDesiredFPS(float fPS)
{
	constexpr float second{ 1.f };
	m_MaxSleepTime = std::chrono::duration<float>(second / fPS);
}

void Time::Init()
{
	m_LastPoint = std::chrono::high_resolution_clock::now();
}

float Time::GetElapsed() const
{
	return m_DeltaTime;
}

float Time::GetTotal() const
{
	return std::chrono::duration<float>(m_CurrentPoint - m_Start).count();
}

std::chrono::duration<float> Time::GetRemainingSleepTime() const
{
	const auto timeInFrame{ std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - m_CurrentPoint) };
	if(timeInFrame < m_MaxSleepTime)
	{
		return m_MaxSleepTime - timeInFrame;
	}
	return std::chrono::duration<float>(0.f);
}

