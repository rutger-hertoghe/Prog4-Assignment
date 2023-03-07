#include "GameObject.h"

#include <string>
#include <ranges>

#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "TextureComponent.h"

using namespace dae;

GameObject::~GameObject()
{
	// View values makes sure that the element returned is the value in the ordered map (not the key/value pair)
	/*for(const auto& pComponent : m_pComponents | std::views::values) 
	{
		delete pComponent;
	}*/
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

void dae::GameObject::SetPosition(float x, float y)
{
	// TODO: update this to reflect world position being set
	m_WorldTransform.SetPosition(x, y, 0.0f);
}

const Transform& GameObject::GetWorldTransform() const
{
	return m_WorldTransform;
}

const Transform& GameObject::GetLocalTransform() const
{
	return m_LocalTransform;
}

std::shared_ptr<GameObject> dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::SetParent(const std::shared_ptr<GameObject>& pNewParent)
{
	if(m_pParent)
	{
		m_pParent->RemoveChild(shared_from_this());
	}
	m_pParent = pNewParent;
	if(pNewParent)
	{
		pNewParent->AddChild(shared_from_this());
	}
	// Update position, rotation & scale
}

int dae::GameObject::GetChildCount() const
{
	return static_cast<int>(m_pChildren.size());
}

shared_ptr<GameObject> dae::GameObject::GetChildAt(int idx)
{
	return m_pChildren[idx];
}

void dae::GameObject::AddChild(const std::shared_ptr<GameObject>& pChild)
{
	m_pChildren.emplace_back(pChild);
}

void dae::GameObject::RemoveChild(const std::shared_ptr<GameObject>& pChild)
{
	// TODO: Child might be removed from parent but is still in scene!
	// Remove from scene here if you want true deletion, or implement removal from parent objects in scene delete of object
	// => Best decision: remove from scene
	// Alternative: Remove is true removal, Detach() is a separate function that deletes the child from the parent, but doesn't remove it from scene
	erase_if(m_pChildren, [&](const shared_ptr<GameObject>& pObj)
		{
			return pChild == pObj;
		});
}
