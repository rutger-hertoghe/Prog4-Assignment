#include "TimerComponent.h"
#include "Time.h"

dae::TimerComponent::TimerComponent(GameObject* pGameObject, float expirationTime, bool isActive, bool isRepeating, const std::function<void()>& action)
	: Component(pGameObject)
	, ExecuteAction{ action }
	, m_ExpirationTime{expirationTime}
	, m_IsRepeating{isRepeating}
	, m_ElapsedTime{0.f}
	, m_IsActive(isActive)
{
}

void dae::TimerComponent::Update()
{
	if (!m_IsActive) return;

	const auto deltaTime{ Time::GetInstance().GetElapsed() };

	m_ElapsedTime += deltaTime;
	if (m_ElapsedTime < m_ExpirationTime) return;

	ExecuteAction();

	if(!m_IsRepeating)
	{
		m_IsActive = false;
		return;
	}

	m_ElapsedTime -= m_ExpirationTime;
}
