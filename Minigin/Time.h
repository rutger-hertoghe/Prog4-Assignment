#pragma once
#include <chrono>

#include "Singleton.h"

class Time final : public dae::Singleton<Time>
{
public:
	void Update();

	[[nodiscard]] float GetElapsed() const;
	[[nodiscard]] float GetTotal() const;

private:
	friend class Singleton<Time>;
	Time();
	std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_LastPoint;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_CurrentPoint;
	float m_DeltaTime{0.f};
};

