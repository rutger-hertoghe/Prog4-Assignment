#include "GameObject.h"

#include "Component.h"
#include "TextureComponent.h"
#include "Transform.h"
#include "TransformComponent.h"

#include <ranges>

using namespace dae;

dae::GameObject::GameObject(const std::string& name)
	: GameObject(name, Transform{})
{}

dae::GameObject::GameObject(const std::string& name, const Transform& transform)
	: m_Name(name)
	, m_pParent(nullptr)
{
	RequireComponent<TransformComponent>(transform);
}

void GameObject::Update()
{
	for(const auto& pComponent : m_pComponents | std::views::values)
	{
		pComponent->Update();
	}

	DeleteMarkedComponents();
}

void GameObject::Render() //const
{
	if (const auto textureComponent{ GetComponent<TextureComponent>() })
	{
		textureComponent->Render();
	}
}

GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::SetParent(GameObject* pNewParent, bool keepWorldPosition)
{
	// TODO: QUESTION in what regard should I foolproof my code?
	if (pNewParent == m_pParent) return;

	if(pNewParent == this)
	{
		std::cout << "Tried setting parent of GameObject to itself, which would lead to recursion and stack overflow!\n";
		return;
	}

	if(!pNewParent)
	{
		std::cout << "SetParent should not be used to detach GameObject from parent!\n"
				  << "Use DetachFromParent() instead!\n";
		return;
	}

	// TODO: doesn't do rotation stuff properly yet (see TransformComponent::CalculateLocalTransformTo() as well)
	const auto pTransform = GetComponent<TransformComponent>();
	if (keepWorldPosition)
	{
		pTransform->SetLocalTransform(pTransform->CalculateLocalTransformTo(pNewParent));
	}
	else
	{
		pTransform->ForceDirty();
	}

	if(m_pParent)
	{
		m_pParent->RemoveChild(this);
	}

	m_pParent = pNewParent;

	if(pNewParent)
	{
		pNewParent->AddChild(this);
	}
}

void dae::GameObject::DetachFromParent(bool keepWorldPosition)
{
	// TODO: make sure this works properly
	const auto pTransform = GetComponent<TransformComponent>();
	if(keepWorldPosition)
	{
		pTransform->SetLocalTransform(pTransform->GetWorldTransform());
	}
	else
	{
		pTransform->ForceDirty();
	}

	if(m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
}

int dae::GameObject::GetChildCount() const
{
	return static_cast<int>(m_pChildren.size());
}

GameObject* dae::GameObject::GetChildAt(int idx) const
{
	return m_pChildren[idx];
}

std::vector<GameObject*> dae::GameObject::GetChildren()
{
	return m_pChildren;
}

std::string dae::GameObject::GetName() const
{
	return m_Name;
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.push_back(pChild);
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	// TODO: Child might be removed from parent but is still in scene!
	// Remove from scene here if you want true deletion, or implement removal from parent objects in scene delete of object
	// => Best decision: remove from scene
	// Alternative: Remove is true removal, Detach() is a separate function that deletes the child from the parent, but doesn't remove it from scene
	erase_if(m_pChildren, [&](GameObject* pObj)
		{
			return pChild == pObj;
		});
}

void dae::GameObject::RemoveDependentComponents(Component* pComponent)
{
	const auto& pDependentTypes{ pComponent->GetDependentComponentTypes() };
	for(const auto& type : pDependentTypes)
	{
		// If there is no component in the map, don't do anything to prevent errors
		if (!m_pComponents.contains(type)) continue;

		const auto pDependentComponent{ m_pComponents.at(type).get() };
		RemoveDependentComponents(pDependentComponent);
		m_pComponentTypesToDelete.push_back(type);
	}
}

void dae::GameObject::DeleteMarkedComponents()
{
	if (m_pComponentTypesToDelete.empty()) return;

	for (const auto& type : m_pComponentTypesToDelete)
	{
		std::cout << "Deleted: " << type.name() << "\n";
		m_pComponents.erase(type);
	}
	m_pComponentTypesToDelete.clear();
}
