#include "GameObject.h"

#include <string>
#include "GameObject.h"

#include <ranges>


#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"
#include "TextureComponent.h"

using namespace dae;

GameObject::~GameObject()
{
	for(const auto pComponent : m_pComponents)
	{
		delete pComponent.second;
	}
}

void GameObject::Update()
{
	for(const auto pComponent : m_pComponents | std::views::values)
	{
		pComponent->Update();
	}
}

void GameObject::Render() //const
{
	// TODO: cache this?
	const auto textureComponent{ GetComponent<TextureComponent>() };
	textureComponent->Render();

	/*for(const auto pComponent : m_pComponents | std::views::values)
	{
		pComponent->Render();
	}*/
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

const Transform& GameObject::GetTransform() const
{
	return m_transform;
}
