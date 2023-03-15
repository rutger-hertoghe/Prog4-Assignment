#pragma once
#include <glm/vec2.hpp>

#include "Component.h"
#include "Transform.h"

namespace dae
{
	// TODO: clean up constructor stuff
	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(GameObject* pOwner, const glm::vec2& position = { 0.f, 0.f }, float rotation = 0.f);
		explicit TransformComponent(GameObject* pOwner, const Transform& transform);

		virtual void Update() override;

		void SetLocalPosition(const glm::vec2& position);

		[[nodiscard]] const glm::vec2& GetWorldPosition();

	private:

		Transform m_LocalTransform;
		Transform m_WorldTransform;

		bool m_IsDirty;

		void SetDirty();

		void UpdateWorldTransform();
	};



	/*class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(GameObject* pParent, const glm::vec2& position = { 0.f, 0.f }, float rotation = 0.f, const glm::vec2& scale = { 1.f, 1.f });
		explicit TransformComponent(GameObject* pParent, const Transform& transform);

		void Update() override;

		void SetLocalPosition(const glm::vec2& pos);
		void SetLocalRotation(float rotation);
		void SetLocalScale(const glm::vec2& scale);

		void AddToLocalPosition(const glm::vec2& pos);
		void AddToLocalRotation(float angle);
		void ModifyLocalScale(float scalar);
		void ModifyLocalScale(const glm::vec2& scalars);
		void ModifyLocalScale(float xScalar, float yScalar);

		[[nodiscard]] const dae::Transform& GetWorldTransform();
		[[nodiscard]] const glm::vec2& GetWorldPosition();
		[[nodiscard]] const glm::vec2& GetWorldScale();
		[[nodiscard]] float GetWorldRotation();

		void UpdateWorldTransform();

	private:
		Transform m_LocalTransform;
		Transform m_WorldTransform;

		bool m_IsDirty;

		void SetDirty();
	};*/
}
