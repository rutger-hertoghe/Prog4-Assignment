#pragma once
#include "Component.h"
namespace dae
{
	class TransformComponent;

	class RotatorComponent final : public Component
	{
	public:
		// TODO: BIG SIX
		explicit RotatorComponent(GameObject* pGameObject, float angularSpeed);

		virtual void Update() override;

	private:
		float m_AngularSpeed;
		TransformComponent* m_Transform;
	};
}


