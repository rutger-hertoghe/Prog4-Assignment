#include "GameObject.h"

#include <string>
#include "GameObject.h"

#include <ranges>


#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

using namespace dae;

GameObject::~GameObject()
{
	for(const auto pComponent : m_pComponents)
	{
		delete pComponent.second;
	}
}

void dae::GameObject::SetComponentParent(Component* pComponent)
{
	// Todo: find better solution, this seems a little hacky
	pComponent->SetParentObject(this);
}

void GameObject::Update()
{
	for(const auto pComponent : m_pComponents | std::views::values)
	{
		pComponent->Update();
	}
}

void GameObject::Render() const
{
	for(const auto pComponent : m_pComponents | std::views::values)
	{
		pComponent->Render();
	}	
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

const Transform& GameObject::GetTransform() const
{
	return m_transform;
}
