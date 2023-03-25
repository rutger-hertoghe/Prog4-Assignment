#include "TextureComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "TransformComponent.h"

dae::TextureComponent::TextureComponent(GameObject* pGameObject, const std::string& filename)
	: TextureComponent(pGameObject)
{
	SetTexture(filename);
}

dae::TextureComponent::TextureComponent(GameObject* pParent)
	: Component(pParent)
	, m_Width{0}
	, m_Height{0}
{
	m_pTransformComponent = pParent->RequireComponent<TransformComponent>();
}

void dae::TextureComponent::Update()
{
	// No update functionality
}

void dae::TextureComponent::Render() const
{
	if (m_Texture == nullptr) return;
	if(m_pTransformComponent)
	{
		const auto pos = m_pTransformComponent->GetWorldTransform().m_Position;
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, static_cast<float>(m_Width), static_cast<float>(m_Height));
	}
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	SetSize(m_Texture->GetSize().x, m_Texture->GetSize().y);
}

void dae::TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
{
	m_Texture = pTexture;
	SetSize(m_Texture->GetSize().x, m_Texture->GetSize().y);
}

void dae::TextureComponent::SetSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}
