#pragma once
#include <string>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		explicit TextureComponent(GameObject* pParent, const std::string& filename);
		explicit TextureComponent(GameObject* pParent);

		virtual ~TextureComponent() override = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other)
			:Component(std::move(other))
		{
			m_Texture = other.m_Texture;
		}
		TextureComponent& operator=(TextureComponent&& other)
		{
			Component::operator=(std::move(other));
			m_Texture = other.m_Texture;
		}

		//virtual void Start() override;
		virtual void Update() override;
		void Render() const;

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);

	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}


