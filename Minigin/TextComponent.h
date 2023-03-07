#pragma once
#include "Component.h"
#include "ResourceManager.h"

namespace dae
{
	class Font;
	class TextureComponent;

	class TextComponent final : public Component
	{
	public:
		explicit TextComponent(GameObject* pParent, const std::string& text = "Text not set!", std::shared_ptr<Font> font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
		virtual ~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update() override;

		void SetText(const std::string& text);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;

		TextureComponent* m_pTextureComponent;
	};
}


