#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "Time.h"

dae::RotatorComponent::RotatorComponent(GameObject* pGameObject, float angularSpeed)
	: Component{ pGameObject }
	, m_AngularSpeed{ angularSpeed }
{
	m_pTransformComponent = GetGameObject()->RequireComponent<TransformComponent>();
}

void dae::RotatorComponent::Update()
{
	const auto deltaTime = Time::GetInstance().GetElapsed();
	if(m_pTransformComponent)
	{
		m_pTransformComponent->Rotate(deltaTime * m_AngularSpeed);
	}
}
