#include "TextureComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(GameObject* pParent, const std::string& filename)
	: Component(pParent)
{
	SetTexture(filename);
}

dae::TextureComponent::TextureComponent(GameObject* pParent)
	: Component(pParent)
{
}

void dae::TextureComponent::Update()
{
	// No update functionality
}

void dae::TextureComponent::Render() const
{
	if (m_Texture == nullptr) return;

	const auto pos = GetParentObject()->GetTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	// TODO: some bad stuff here?
	m_Texture = pTexture;
}