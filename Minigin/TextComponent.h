#pragma once
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final : public Component
	{
	public:
		TextComponent() = delete;
		TextComponent(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() override = default;


		TextComponent(const TextComponent& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		//void Start() override;
		void Render() override;
		void Update() override;

		void SetText(const std::string& text);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}


