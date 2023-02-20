#pragma once
#include <chrono>

#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	void Update();

	float GetElapsed() const;
	float GetTotal() const;

private:
	friend class Singleton<Time>;
	Time();
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastPoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> currentPoint;
	float deltaTime{0.f};
};

