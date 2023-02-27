#include "TextureComponent.h"

#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename)
{
	SetTexture(filename);
}

//void dae::TextureComponent::Start()
//{
//	// No start behaviour
//}

void dae::TextureComponent::Update()
{
	// No update functionality
}

void dae::TextureComponent::Render()
{
	auto pos = m_pParentObject->GetTransform().GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}