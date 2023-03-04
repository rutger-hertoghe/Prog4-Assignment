#include "TextComponent.h"

#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TextureComponent.h"

class TextureComponentNotFound{};

dae::TextComponent::TextComponent(GameObject* pParent, const std::string& text, std::shared_ptr<Font> font)
	: Component(pParent)
	, m_NeedsUpdate{true}
	, m_Text{text}
	, m_Font(std::move(font))
{
	m_pTextureComponent = GetParentObject()->GetComponent<TextureComponent>();
	// TODO: use assert instead of throw?
	if(m_pTextureComponent == nullptr)
	{
		std::cerr << "Necessary texture component not found!\n";
		throw TextureComponentNotFound();
	}
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextureComponent->SetTexture(std::make_shared<Texture2D>(texture));
		//m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

