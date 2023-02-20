#include "Time.h"

Time::Time()
{
	start = std::chrono::high_resolution_clock::now();
}

void Time::Update()
{
	currentPoint = std::chrono::high_resolution_clock::now();

	deltaTime = std::chrono::duration<float>(currentPoint - lastPoint).count();
	lastPoint = currentPoint;
}

float Time::GetElapsed() const
{
	return deltaTime;
}

float Time::GetTotal() const
{
	return std::chrono::duration<float>(currentPoint - start).count();
}
