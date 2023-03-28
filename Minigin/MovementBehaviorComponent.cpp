#include "MovementBehaviorComponent.h"

#include "GameObject.h"
#include "Time.h"

dae::MovementBehaviorComponent::MovementBehaviorComponent(GameObject* pGameObject, float speed)
	: Component(pGameObject)
	, m_Speed(speed)
	, m_MovementDirection(0, 0)
{
	// Presence of TransformComponent is guaranteed
	m_pTransformComponent = pGameObject->GetComponent<TransformComponent>();
}

void dae::MovementBehaviorComponent::Update()
{
	constexpr float movementThreshold{ 0.0001f };
	if(glm::length(m_MovementDirection) > movementThreshold)
	{
		m_pTransformComponent->Move(glm::normalize(m_MovementDirection) * m_Speed * Time::GetInstance().GetElapsed());
	}
	m_MovementDirection = { 0.f, 0.f };
}

void dae::MovementBehaviorComponent::AddMovementInDirection(const glm::vec2& direction)
{
	m_MovementDirection += glm::normalize(direction);
}
