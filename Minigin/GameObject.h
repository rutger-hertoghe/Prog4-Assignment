#pragma once
#include <memory>
#include <string>
//#include "TypeMap.h"
//#include "OwningTypeMap.h"
#include <vector>
#include <unordered_map>
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
		void SetParent(GameObject* pNewParent, bool keepWorldPosition = true);
		void DetachFromParent(bool keepWorldPosition = true);

		[[nodiscard]] int GetChildCount() const;
		[[nodiscard]] GameObject* GetChildAt(int idx) const;
		[[nodiscard]] std::vector<GameObject*> GetChildren();

	private:
		std::unordered_map<const type_info*, Component*> m_pComponents;

		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);
	};



	// |--------------------------------|
	// | TEMPLATED FUNCTION DEFINITIONS |
	// |--------------------------------|

	template<typename T_Component>
	T_Component* GameObject::GetComponent()
	{
		if(m_pComponents.contains(&typeid(T_Component)))
		{
			return static_cast<T_Component*>(m_pComponents.at(&typeid(T_Component)));
		}
		std::cerr << typeid(T_Component).name() << " was not found in GameObject!\n";
		return nullptr;
	}

	template<typename T_Component, typename... Args, typename>
	T_Component* GameObject::AddComponent(Args... args)
	{		 
		if(m_pComponents.contains(&typeid(T_Component)))
		{
			std::cerr << "Component already exists in map\n";
			return static_cast<T_Component*>(m_pComponents[&typeid(T_Component)]);
		}

		auto pComponent = new T_Component(this, args...);
		m_pComponents.insert(std::make_pair(&typeid(T_Component), pComponent));
		return pComponent;
	}

	template<typename T_Component>
	bool GameObject::RemoveComponent()
	{
		// TODO: can probably skip over GetComponent here
		auto pComponent = GetComponent<T_Component>();
		if (pComponent == nullptr) return false;

		delete pComponent;

		return m_pComponents.erase<T_Component>();
	}

	template<typename T_Component, typename... Args, typename>
	T_Component* GameObject::RequireComponent(Args... args)
	{
		if(m_pComponents.contains(&typeid(T_Component)))
		{
			return static_cast<T_Component*>(m_pComponents[&typeid(T_Component)]);
		}
		std::cout << "Automatically attaching " << typeid(T_Component).name() << " to object!\n";
		return AddComponent<T_Component>(args...);
	}
}
