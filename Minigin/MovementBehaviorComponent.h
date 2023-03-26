#ifndef MOVEMENT_BEHAVIOR_COMPONENT_H
#define MOVEMENT_BEHAVIOR_COMPONENT_H

#include <glm/vec2.hpp>

#include "Component.h"
#include "TransformComponent.h"

namespace dae
{
	class MovementBehaviorComponent final : public Component
	{
	public:
		explicit MovementBehaviorComponent(GameObject* pGameObject, float speed);
		~MovementBehaviorComponent() override = default;

		MovementBehaviorComponent(const MovementBehaviorComponent& other) = delete;
		MovementBehaviorComponent& operator=(const MovementBehaviorComponent& other) = delete;
		MovementBehaviorComponent(MovementBehaviorComponent&& other) = delete;
		MovementBehaviorComponent& operator=(MovementBehaviorComponent&& other) = delete;

		virtual void Update() override;

		void AddMovementInDirection(const glm::vec2& direction);
	private:
		float m_Speed;
		glm::vec2 m_MovementDirection;
		TransformComponent* m_pTransformComponent;
	};
}
#endif