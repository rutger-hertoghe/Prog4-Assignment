#include "MoveComponent.h"
#include "TransformComponent.h"
#include "Time.h"

dae::MoveComponent::MoveComponent(GameObject* pGameObject, const glm::vec2& velocity)
	: Component{ pGameObject }
	, m_Velocity{velocity}
{
	pGameObject->RequireComponent<TransformComponent>();
}

void dae::MoveComponent::Update()
{
	if(const auto pTransform = GetGameObject()->GetComponent<TransformComponent>())
	{
		const float deltaTime{ Time::GetInstance().GetElapsed() };
		pTransform->Move(m_Velocity * deltaTime);
	}
}
