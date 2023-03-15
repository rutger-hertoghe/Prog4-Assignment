#pragma once
#include <memory>
#include <string>
#include "TypeMap.h"
#include <stdexcept>
#include <iostream>
#include "Component.h"

//#include "TransformComponent.h"

namespace dae
{
	class Texture2D;
	class Component;
	class TransformComponent;
	struct Transform;

	class GameObject final
	{
	public:
		// BIG SIX
		explicit GameObject();
		explicit GameObject(const Transform& transform);
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// GAMELOOP FUNCTIONS
		void Update();
		void Render(); //const;

		// COMPONENTS
		template<typename T_Component>
		T_Component* GetComponent(); //const; // TODO: QUESTION why does setting const here break my code?

		template<typename T_Component, typename... Args, typename = std::enable_if_t<std::is_constructible_v<T_Component, GameObject*, Args...>>>
		T_Component* AddComponent(Args... args);

		template<typename T_Component>
		bool RemoveComponent();

		template<typename T_Component, typename... Args, typename = std::enable_if_t<std::is_constructible_v<T_Component, GameObject*, Args...>>>
		T_Component* RequireComponent(Args... args);

		// PARENTING & CHILDRENING (?)
		[[nodiscard]] GameObject* GetParent() const;
		// TODO: Add option to keep world position
		void SetParent(GameObject* pNewParent);

		[[nodiscard]] int GetChildCount() const;
		[[nodiscard]] GameObject* GetChildAt(int idx) const;
		[[nodiscard]] std::vector<GameObject*> GetChildren();

	private:
		TypeMap<Component*> m_pComponents;

		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
	};



	// |--------------------------------|
	// | TEMPLATED FUNCTION DEFINITIONS |
	// |--------------------------------|

	template <typename T_Component>
	T_Component* GameObject::GetComponent() //const
	{
		try
		{
			auto pComponent{ m_pComponents.at<T_Component>() };
			return static_cast<T_Component*>(pComponent);
		}
		catch(TypeNotInMapException&)
		{
			return nullptr;
		}
	}

	template<typename T_Component, typename... Args, typename>
	T_Component* GameObject::AddComponent(Args... args)
	{
		auto pComponent = new T_Component(this, args...);
		m_pComponents.emplace<T_Component>(pComponent);
		return static_cast<T_Component*>(pComponent);
	}

	template<typename T_Component>
	bool GameObject::RemoveComponent()
	{
		auto pComponent = GetComponent<T_Component>();
		if (pComponent == nullptr) return false;

		delete pComponent;

		return m_pComponents.erase<T_Component>();
	}

	template<typename T_Component, typename... Args, typename>
	T_Component* GameObject::RequireComponent(Args... args)
	{
		auto pRequiredComponent = GetComponent<T_Component>();
		if (pRequiredComponent == nullptr)
		{
			// TODO: remove because of cluttering & lack of clarity in console?
			std::cout << "Necessary component not found! Automatically attaching " << typeid(T_Component).name() <<" to object!\n";

			pRequiredComponent = AddComponent<T_Component>(args...);
		}
		return pRequiredComponent;
	}
}
