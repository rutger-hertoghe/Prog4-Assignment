#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "TransformComponent.h"

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
		~GameObject() = default;

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
		std::unordered_map<const type_info*, std::unique_ptr<Component>> m_pComponents;

		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		void RemoveDependentComponents(Component* pComponent);
		void DeleteMarkedComponents();

		// To prevent deletion in Update(), which may cause undefined behavior
		std::vector<const type_info*> m_pComponentTypesToDelete;
	};



	// |--------------------------------|
	// | TEMPLATED FUNCTION DEFINITIONS |
	// |--------------------------------|

	// Gets the component of the type specified by the template argument
	// If none is found, returns 'nullptr'.
	template<typename T_Component>
	T_Component* GameObject::GetComponent()
	{
		if(m_pComponents.contains(&typeid(T_Component)))
		{
			return static_cast<T_Component*>(m_pComponents.at(&typeid(T_Component)).get());
		}
		return nullptr;
	}

	// Adds a component to the GameObject of the type specified as the template argument, 
	// component constructor arguments can/must be given as arguments.
	//
	// If the component is dependent on other components, these will be automatically
	// added as well.
	template<typename T_Component, typename... Args, typename>
	T_Component* GameObject::AddComponent(Args... args)
	{
		// TODO: Add with [] as well? (suggestion Tanguy)
		if(m_pComponents.contains(&typeid(T_Component)))
		{
			std::cerr << "Component already exists in map\n";
			return static_cast<T_Component*>(m_pComponents[&typeid(T_Component)].get());
		}

		m_pComponents.insert(std::make_pair(&typeid(T_Component), std::make_unique<T_Component>(this, args...)));
		return GetComponent<T_Component>();
	}

	// Marks the component of the template argument type for deletion, along with all the components dependent on it.
	template<typename T_Component>
	bool GameObject::RemoveComponent()
	{
		if(typeid(T_Component) == typeid(TransformComponent))
		{
			std::cout << "Removing the transform of a GameObject is not allowed!\n";
			return false;
		}

		if(auto pComponent{ GetComponent<T_Component>() })
		{
			RemoveDependentComponents(pComponent);
			m_pComponentTypesToDelete.push_back(&typeid(T_Component));
			return true;
		}
		
		return false;
	}

	template<typename T_Component, typename... Args, typename>
	T_Component* GameObject::RequireComponent(Args... args)
	{
		if(m_pComponents.contains(&typeid(T_Component)))
		{
			return static_cast<T_Component*>(m_pComponents[&typeid(T_Component)].get());
		}
		std::cout << "Automatically attaching " << typeid(T_Component).name() << " to object!\n";
		return AddComponent<T_Component>(args...);
	}
}
#endif