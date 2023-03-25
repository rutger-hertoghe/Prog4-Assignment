#ifndef TIMER_COMPONENT_H
#define TIMER_COMPONENT_H

#include "Component.h"

#include <functional>

namespace dae
{
	class TimerComponent final : public Component
	{
	public:
		explicit TimerComponent(GameObject* pGameObject, float expirationTime, bool isActive, bool isRepeating, const std::function<void()>& action);
		~TimerComponent() override = default;

		TimerComponent(const TimerComponent* other) = delete;
		TimerComponent& operator=(const TimerComponent* other) = delete;
		TimerComponent(TimerComponent&& other) = delete;
		TimerComponent& operator=(TimerComponent&& other) = delete;

		virtual void Update() override;

	private:
		std::function<void()> ExecuteAction;
		float m_ExpirationTime;
		float m_ElapsedTime;
		bool m_IsRepeating;
		bool m_IsActive;
	};
}
#endif