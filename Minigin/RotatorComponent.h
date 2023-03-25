#ifndef ROTATOR_COMPONENT_H
#define ROTATOR_COMPONENT_H

#include "Component.h"

namespace dae
{
	class TransformComponent;

	class RotatorComponent final : public Component
	{
	public:
		explicit RotatorComponent(GameObject* pGameObject, float angularSpeed);
		~RotatorComponent() override = default;

		RotatorComponent(const RotatorComponent* other) = delete;
		RotatorComponent& operator=(const RotatorComponent* other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		virtual void Update() override;

	private:
		float m_AngularSpeed;

		TransformComponent* m_pTransformComponent;
	};
}
#endif