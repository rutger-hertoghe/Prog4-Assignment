#include "MoveComponent.h"
#include "TransformComponent.h"
#include "Time.h"
#include "GameObject.h"

dae::MoveComponent::MoveComponent(GameObject* pGameObject, const glm::vec2& velocity)
	: Component{ pGameObject }
	, m_Velocity{velocity}
{
	// Presence of TransformComponent is guaranteed
	m_pTransformComponent =  pGameObject->GetComponent<TransformComponent>();
}

void dae::MoveComponent::Update()
{
	const float deltaTime{ Time::GetInstance().GetElapsed() };
	m_pTransformComponent->Move(m_Velocity * deltaTime);
}
