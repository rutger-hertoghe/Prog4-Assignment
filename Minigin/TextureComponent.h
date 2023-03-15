#pragma once
#include <string>

#include "Component.h"

namespace dae
{
	class TransformComponent;
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		explicit TextureComponent(GameObject* pOwner, const std::string& filename);
		explicit TextureComponent(GameObject* pParent);

		virtual ~TextureComponent() override = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		//virtual void Start() override;
		virtual void Update() override;
		void Render() const;

		void SetTexture(const std::string& filename);
		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);

		void SetSize(int width, int height);

	private:
		std::shared_ptr<Texture2D> m_Texture{};
		TransformComponent* m_TransformComponent{};
		int m_Width;
		int m_Height;
	};
}


