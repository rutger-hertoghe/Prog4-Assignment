#include "MoveComponent.h"
#include "TransformComponent.h"
#include "Time.h"

dae::MoveComponent::MoveComponent(GameObject* pGameObject, const glm::vec2& velocity)
	: Component{ pGameObject }
	, m_Velocity{velocity}
{
	m_Transform = pGameObject->RequireComponent<TransformComponent>();
}

void dae::MoveComponent::Update()
{
	const float deltaTime{ Time::GetInstance().GetElapsed() };
	m_Transform->Move(m_Velocity * deltaTime);
}
