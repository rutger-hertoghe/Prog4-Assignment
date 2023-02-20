#pragma once
#include <memory>
#include <vector>

#include "Transform.h"

namespace dae
{
	class Component;

	// todo: this should become final.
	class GameObject 
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename T_Component>
		T_Component* AddComponent(T_Component* pComponent);

	private:
		Transform m_transform{};
		// todo: move this into texture renderer class
		//std::shared_ptr<Texture2D> m_texture{};
		std::vector<Component*> m_Components;
	};

	template<typename T_Component>
	inline T_Component* GameObject::AddComponent(T_Component* pComponent)
	{
		m_Components.push_back(pComponent);
		return pComponent;
	}
}
