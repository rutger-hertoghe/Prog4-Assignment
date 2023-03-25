#ifndef MOVE_COMPONENT_H
#define MOVE_COMPONENT_H

#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class TransformComponent;

	class MoveComponent final : public Component
	{
	public:
		explicit MoveComponent(GameObject* pGameObject, const glm::vec2& velocity);
		~MoveComponent() override = default;

		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) = delete;
		MoveComponent& operator=(MoveComponent& other) = delete;

		virtual void Update() override;

	private:
		glm::vec2 m_Velocity;

		TransformComponent* m_pTransformComponent;
	};
}
#endif