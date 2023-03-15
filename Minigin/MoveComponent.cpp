#include "MoveComponent.h"
#include "TransformComponent.h"
#include "Time.h"

dae::MoveComponent::MoveComponent(GameObject* pOwner, const glm::vec2& velocity)
	: Component{ pOwner }
	, m_Velocity{velocity}
{
	m_Transform = pOwner->RequireComponent<TransformComponent>();
}

void dae::MoveComponent::Update()
{
	const float deltaTime{ Time::GetInstance().GetElapsed() };
	m_Transform->SetLocalPosition(m_Transform->GetWorldPosition() + m_Velocity * deltaTime);
}
