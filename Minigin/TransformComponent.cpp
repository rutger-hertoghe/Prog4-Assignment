#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner, const glm::vec2& position, float rotation)
	: Component{pOwner}
	, m_LocalTransform{position, rotation}
	, m_IsDirty{true}
{
}

dae::TransformComponent::TransformComponent(GameObject* pOwner, const Transform& transform)
	: Component{ pOwner }
	, m_LocalTransform{transform}
	, m_IsDirty{true}
{
}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::SetLocalPosition(const glm::vec2& position)
{
	m_LocalTransform.m_Position = position;
	SetDirty();
}

const glm::vec2& dae::TransformComponent::GetWorldPosition()
{
	if(m_IsDirty)
	{
		UpdateWorldTransform();
	}
	return m_WorldTransform.m_Position;
}

void dae::TransformComponent::SetDirty()
{
	m_IsDirty = true;
	const auto& gameObjectChildren{ GetOwner()->GetChildren() };
	for(const auto& child : gameObjectChildren)
	{
		child->GetComponent<TransformComponent>()->SetDirty();
	}
}

void dae::TransformComponent::UpdateWorldTransform()
{
	if(const auto pParent = GetOwner()->GetParent())
	{
		m_WorldTransform.m_Position = pParent->GetComponent<TransformComponent>()->m_WorldTransform.m_Position + m_LocalTransform.m_Position;
	}
	else
	{
		m_WorldTransform = m_LocalTransform;
	}
	m_IsDirty = false;
}




//dae::TransformComponent::TransformComponent(GameObject* pParent, const glm::vec2& position, float rotation, const glm::vec2& scale)
//	: TransformComponent(pParent, Transform{position, rotation, scale})
//{}
//
//dae::TransformComponent::TransformComponent(GameObject* pParent, const Transform& transform)
//	: Component(pParent)
//	, m_LocalTransform{ transform }
//	, m_WorldTransform{ transform }
//	, m_IsDirty(true)
//{
//}
//
//void dae::TransformComponent::Update()
//{
//	// No contents
//}
//
//void dae::TransformComponent::SetLocalPosition(const glm::vec2& pos)
//{
//	m_LocalTransform.SetPosition(pos);
//	SetDirty();
//}
//
//void dae::TransformComponent::SetLocalRotation(float rotation)
//{
//	m_LocalTransform.SetRotation(rotation);
//	SetDirty();
//}
//
//void dae::TransformComponent::SetLocalScale(const glm::vec2& scale)
//{
//	m_LocalTransform.SetScale(scale);
//	SetDirty();
//}
//
//const glm::vec2& dae::TransformComponent::GetWorldPosition()
//{
//	if(m_IsDirty)
//	{
//		UpdateWorldTransform();
//	}
//	return m_WorldTransform.GetPosition();
//}
//
//const dae::Transform& dae::TransformComponent::GetWorldTransform()
//{
//	if(m_IsDirty)
//	{
//		UpdateWorldTransform();
//	}
//	return m_WorldTransform;
//}
//
//const glm::vec2& dae::TransformComponent::GetWorldScale()
//{
//	if(m_IsDirty)
//	{
//		UpdateWorldTransform();
//	}
//	return m_WorldTransform.GetScale();
//}
//
//float dae::TransformComponent::GetWorldRotation()
//{
//	if (m_IsDirty)
//	{
//		UpdateWorldTransform();
//	}
//	return m_WorldTransform.GetRotation();
//}
//
//void dae::TransformComponent::SetDirty()
//{
//	m_IsDirty = true;
//	const auto& gameObjectChildren{ GetOwner()->GetChildren() };
//	for(const auto& child : gameObjectChildren)
//	{
//		child->GetComponent<TransformComponent>()->SetDirty();
//	}
//}
//
//void dae::TransformComponent::AddToLocalPosition(const glm::vec2& pos)
//{
//	m_LocalTransform.AddPosition(pos);
//	SetDirty();
//}
//
//void dae::TransformComponent::AddToLocalRotation(float angle)
//{
//	m_LocalTransform.AddRotation(angle);
//	SetDirty();
//}
//
//void dae::TransformComponent::ModifyLocalScale(float scalar)
//{
//	m_LocalTransform.RelativeScale(scalar);
//}
//
//void dae::TransformComponent::ModifyLocalScale(const glm::vec2& scalars)
//{
//	m_LocalTransform.RelativeScale(scalars);
//}
//
//void dae::TransformComponent::ModifyLocalScale(float xScalar, float yScalar)
//{
//	m_LocalTransform.RelativeScale({ xScalar, yScalar });
//}
//
//void dae::TransformComponent::UpdateWorldTransform()
//{
//	// TODO: adapt to include scale & rotation
//	auto pParent{ GetOwner()->GetParent() };
//	if (pParent)
//	{
//		auto parentTransform = pParent->GetComponent<TransformComponent>();
//		if (parentTransform)
//		{
//			m_WorldTransform *= (m_LocalTransform * parentTransform->GetWorldTransform());
//		}
//		else
//		{
//			m_WorldTransform = m_LocalTransform;
//		}
//	}
//	m_IsDirty = false;
//}

