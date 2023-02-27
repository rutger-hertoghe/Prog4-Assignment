#include "Time.h"

#include <iostream>

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

float Time::GetElapsed() const
{
	return m_DeltaTime;
}

float Time::GetTotal() const
{
	return std::chrono::duration<float>(m_CurrentPoint - m_Start).count();
}
