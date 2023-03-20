#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "Time.h"

dae::RotatorComponent::RotatorComponent(GameObject* pGameObject, float angularSpeed)
	: Component{ pGameObject }
	, m_AngularSpeed{ angularSpeed }
{
	m_Transform = pGameObject->RequireComponent<TransformComponent>();
}

void dae::RotatorComponent::Update()
{
	const auto deltaTime = Time::GetInstance().GetElapsed();
	m_Transform->Rotate(deltaTime * m_AngularSpeed);
}
