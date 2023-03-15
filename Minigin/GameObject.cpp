#include "GameObject.h"

#include <ranges>

#include "Component.h"
#include "TextureComponent.h"
#include "Transform.h"
#include "TransformComponent.h"

using namespace dae;

dae::GameObject::GameObject()
	: GameObject(Transform{})
{}

dae::GameObject::GameObject(const Transform& transform)
	: m_pParent(nullptr)
{
	RequireComponent<TransformComponent>(transform);
}

GameObject::~GameObject()
{
	// View values makes sure that the element returned is the value in the ordered map (not the key/value pair)
	for(const auto& pComponent : m_pComponents | std::views::values) 
	{
		delete pComponent;
	}
}

void GameObject::Update()
{
	// TODO: if gameObject has ownership over children (which is not the case for you), also update children
	for(const auto& pComponent : m_pComponents | std::views::values)
	{
		pComponent->Update();
	}
}

void GameObject::Render() //const
{
	// TODO: cache this?
	// For now, let's not, as long as components are unique or regular pointers, caching this will cause problems after the texture component gets removed
	const auto textureComponent{ GetComponent<TextureComponent>() };
	if(textureComponent)
	{
		textureComponent->Render();
	}
}

GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::SetParent(GameObject* pNewParent)
{
	if(m_pParent)
	{
		m_pParent->RemoveChild(this);
	}

	m_pParent = pNewParent;

	if(pNewParent)
	{
		pNewParent->AddChild(this);
	}
	// Update position, rotation & scale
	// TODO: add transformation stuff
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

void dae::GameObject::AddChild(GameObject* pChild)
{
	m_pChildren.emplace_back(pChild);
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
