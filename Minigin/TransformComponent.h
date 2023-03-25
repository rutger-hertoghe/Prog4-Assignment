#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H
#include <glm/vec2.hpp>

#include "Component.h"
#include "Transform.h"

namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(GameObject* pGameObject, float x, float y, float rotation = 0.f);
		explicit TransformComponent(GameObject* pGameObject, const glm::vec2& position = { 0.f, 0.f }, float rotation = 0.f);
		explicit TransformComponent(GameObject* pGameObject, const Transform& transform);

		~TransformComponent() override = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		virtual void Update() override;
		
		void SetLocalPosition(const glm::vec2& position);
		void SetLocalRotation(float radians);
		void SetLocalTransform(const Transform& transform);

		void Rotate(float radians);
		void Move(const glm::vec2& displacement);
		void Move(float deltaX, float deltaY);
		
		[[nodiscard]] const glm::vec2& GetLocalPosition() const;
		[[nodiscard]] float GetLocalRotation() const;
		[[nodiscard]] const Transform& GetWorldTransform();

		// TODO: figure out whether this function can be removed
		// USE WITH CAUTION
		void ForceDirty();

		// TODO: make these private, eventually
		[[nodiscard]] Transform CalculateLocalTransformTo(GameObject* pGameObject);
		[[nodiscard]] Transform CalculateLocalTransformTo(TransformComponent* pTransformComponent);

	private:

		Transform m_LocalTransform;
		Transform m_WorldTransform;

		bool m_IsDirty;

		void SetDirty();

		void UpdateWorldTransform();
	};
}
#endif