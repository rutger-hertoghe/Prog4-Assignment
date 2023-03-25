#include "MoveComponent.h"
#include "TransformComponent.h"
#include "Time.h"
#include "GameObject.h"

dae::MoveComponent::MoveComponent(GameObject* pGameObject, const glm::vec2& velocity)
	: Component{ pGameObject }
	, m_Velocity{velocity}
{
	m_pTransformComponent =  pGameObject->RequireComponent<TransformComponent>();
}

void dae::MoveComponent::Update()
{
	if(m_pTransformComponent)
	{
		const float deltaTime{ Time::GetInstance().GetElapsed() };
		m_pTransformComponent->Move(m_Velocity * deltaTime);
	}
}
