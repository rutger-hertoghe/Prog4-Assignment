#pragma once
#include <functional>

#include "Component.h"
namespace dae
{
	// TODO: BIG SIX
	class TimerComponent final : public Component
	{
	public:
		explicit TimerComponent(GameObject* pGameObject, float expirationTime, bool isActive, bool isRepeating, const std::function<void()>& action);

		virtual void Update() override;

	private:
		std::function<void()> ExecuteAction;
		float m_ExpirationTime;
		float m_ElapsedTime;
		bool m_IsRepeating;
		bool m_IsActive;
	};
}
