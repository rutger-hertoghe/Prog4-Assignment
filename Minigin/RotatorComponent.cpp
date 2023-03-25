#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "Time.h"

dae::RotatorComponent::RotatorComponent(GameObject* pGameObject, float angularSpeed)
	: Component{ pGameObject }
	, m_AngularSpeed{ angularSpeed }
{
	pGameObject->RequireComponent<TransformComponent>();
}

void dae::RotatorComponent::Update()
{
	const auto deltaTime = Time::GetInstance().GetElapsed();
	if(const auto pTransform{GetGameObject()->GetComponent<TransformComponent>()})
	{
		pTransform->Rotate(deltaTime * m_AngularSpeed);
	}
}
