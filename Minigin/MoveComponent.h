#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	// TODO: BIG SIX
	class MoveComponent final : public Component
	{
	public:
		explicit MoveComponent(GameObject* pGameObject, const glm::vec2& velocity);

		virtual void Update() override;

	private:
		TransformComponent* m_Transform;
		glm::vec2 m_Velocity;
	};
}
