#include "TransformComponent.h"

class NoTransformOnGameObject
{
	NoTransformOnGameObject()
	{
		std::cout << "ERROR: Passed GameObject does not have a transform component attached!\n";
	}
};

dae::TransformComponent::TransformComponent(GameObject* pGameObject, float x, float y, float rotation)
	: TransformComponent(pGameObject, Transform{x, y, rotation})
{}

dae::TransformComponent::TransformComponent(GameObject* pGameObject, const glm::vec2& position, float rotation)
	: TransformComponent(pGameObject, Transform(position, rotation))
{}

dae::TransformComponent::TransformComponent(GameObject* pGameObject, const Transform& transform)
	: Component{ pGameObject }
	, m_LocalTransform{ transform }
	, m_WorldTransform{ transform }
	, m_IsDirty{ false }
{
}

void dae::TransformComponent::Update()
{
}

void dae::TransformComponent::SetLocalPosition(const glm::vec2& position)
{
	m_LocalTransform.m_Position = position;

	m_LocalTransform.ConstructMatrix();
	SetDirty();
}

void dae::TransformComponent::SetLocalRotation(float radians)
{
	m_LocalTransform.m_Rotation = radians;

	m_LocalTransform.ConstructMatrix();
	SetDirty();
}

void dae::TransformComponent::SetLocalTransform(const Transform& transform)
{
	m_LocalTransform = transform;
	// TODO: figure out whether below call is redundant, at first glance it probably is
	m_LocalTransform.ConstructMatrix();
	SetDirty();
}

void dae::TransformComponent::Rotate(float radians)
{
	m_LocalTransform.m_Rotation += radians;

	m_LocalTransform.ConstructMatrix();
	SetDirty();
}

void dae::TransformComponent::Move(const glm::vec2& displacement)
{
	m_LocalTransform.m_Position += displacement;

	m_LocalTransform.ConstructMatrix();
	SetDirty();
}

void dae::TransformComponent::Move(float deltaX, float deltaY)
{
	m_LocalTransform.m_Position.x += deltaX;
	m_LocalTransform.m_Position.y += deltaY;

	m_LocalTransform.ConstructMatrix();
	SetDirty();
}

const glm::vec2& dae::TransformComponent::GetLocalPosition() const
{
	return m_LocalTransform.m_Position;
}

float dae::TransformComponent::GetLocalRotation() const
{
	return m_LocalTransform.m_Rotation;
}


const dae::Transform& dae::TransformComponent::GetWorldTransform()
{
	if (m_IsDirty)
	{
		UpdateWorldTransform();
	}
	return m_WorldTransform;
}

void dae::TransformComponent::ForceDirty()
{
	m_LocalTransform.ConstructMatrix();
	SetDirty();
}

void dae::TransformComponent::SetDirty()
{
	m_IsDirty = true;
	const auto& gameObjectChildren{ GetGameObject()->GetChildren() };
	for(const auto& child : gameObjectChildren)
	{
		child->GetComponent<TransformComponent>()->SetDirty();
	}
}

void dae::TransformComponent::UpdateWorldTransform()
{
	if(const auto pParent = GetGameObject()->GetParent())
	{
		const auto& parentWorld { pParent->GetComponent<TransformComponent>()->GetWorldTransform()};

		m_WorldTransform.m_TransformMatrix = m_LocalTransform.m_TransformMatrix * parentWorld.m_TransformMatrix;
		m_WorldTransform.ExtractDataFromMatrix();
	}
	else
	{
		m_WorldTransform = m_LocalTransform;
	}
	m_IsDirty = false;
}

dae::Transform dae::TransformComponent::CalculateLocalTransformTo(GameObject* pGameObject)
{
	const auto pGameObjectTransform = pGameObject->GetComponent<TransformComponent>();

	return CalculateLocalTransformTo(pGameObjectTransform);
}

dae::Transform dae::TransformComponent::CalculateLocalTransformTo(TransformComponent* pTransformComponent)
{
	const auto parentRotation{ pTransformComponent->GetWorldTransform().m_Rotation };
	const auto cos(cosf(-parentRotation));
	const auto sin(sinf(-parentRotation));

	auto newLocalPosition{ GetWorldTransform().m_Position - pTransformComponent->GetWorldTransform().m_Position };
	newLocalPosition.x = (cos * newLocalPosition.x - sin * newLocalPosition.y);
	newLocalPosition.y = (sin * newLocalPosition.x + cos * newLocalPosition.y);

	return Transform{ newLocalPosition};
}

