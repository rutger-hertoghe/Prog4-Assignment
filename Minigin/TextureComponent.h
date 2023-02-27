#pragma once
#include <string>

#include "Component.h"

namespace dae
{
	class Texture2D;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent() = delete;
		TextureComponent(const std::string& filename);

		virtual ~TextureComponent() override = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		//virtual void Start() override;
		virtual void Update() override;
		virtual void Render() override;

		void SetTexture(const std::string& filename);

	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
}


