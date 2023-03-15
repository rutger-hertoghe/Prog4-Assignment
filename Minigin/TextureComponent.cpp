#include "TextureComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "TransformComponent.h"

dae::TextureComponent::TextureComponent(GameObject* pParent, const std::string& filename)
	: TextureComponent(pParent)
{
	SetTexture(filename);
	m_Width = m_Texture->GetSize().x;
	m_Height = m_Texture->GetSize().y;
}

dae::TextureComponent::TextureComponent(GameObject* pParent)
	: Component(pParent)
	, m_Width{0}
	, m_Height{0}
{
	m_TransformComponent = pParent->RequireComponent<TransformComponent>();
}

void dae::TextureComponent::Update()
{
	// No update functionality
}

void dae::TextureComponent::Render() const
{
	if (m_Texture == nullptr) return;

	const auto pos = m_TransformComponent->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, static_cast<float>(m_Width), static_cast<float>(m_Height));
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_Texture = pTexture;
}

void dae::TextureComponent::SetSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}
