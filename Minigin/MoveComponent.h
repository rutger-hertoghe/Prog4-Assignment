#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace dae
{
	class TransformComponent;
	// TODO: BIG SIX
	class MoveComponent final : public Component
	{
	public:
		explicit MoveComponent(GameObject* pGameObject, const glm::vec2& velocity);

		virtual void Update() override;

	private:
		glm::vec2 m_Velocity;

		TransformComponent* m_pTransformComponent;
	};
}
