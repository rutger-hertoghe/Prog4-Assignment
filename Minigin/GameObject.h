#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <typeindex>

namespace dae
{
	class Component;
	class TransformComponent;
	struct Transform;
	class Subject;

	class GameObject final
	{
	public:
		// BIG SIX
		explicit GameObject(const std::string& name);
		explicit GameObject(const std::string& name, const Transform& transform);
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

		[[nodiscard]] std::string GetName() const; // TODO: could maybe be const std::string&

	private:
		std::string m_Name;

		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_pComponents;
		//std::unordered_map<std::string, Subject*> m_pEvents;

		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		void RemoveDependentComponents(Component* pComponent);
		void DeleteMarkedComponents();

		// To prevent deletion in Update(), which may cause undefined behavior
		std::vector<std::type_index> m_pComponentTypesToDelete;
	};



	// |--------------------------------|
	// | TEMPLATED FUNCTION DEFINITIONS |
	// |--------------------------------|

	// Gets the component of the type specified by the template argument
	// If none is found, returns 'nullptr'.
	template<typename T_Component>
	T_Component* GameObject::GetComponent()
	{
		const auto type{ std::type_index{typeid(T_Component)} };
		if(m_pComponents.contains(type))
		{
			return static_cast<T_Component*>(m_pComponents.at(type).get());
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
		const auto type{ std::type_index{typeid(T_Component)} };
		// TODO: Add with [] as well? (suggestion Tanguy) -> Tried this, didn't seem to work. Did not fully investigate yet
		if(m_pComponents.contains(type))
		{
			std::cerr << "Component already exists in map\n";
			return static_cast<T_Component*>(m_pComponents[type].get());
		}

		m_pComponents.insert(std::make_pair(type, std::make_unique<T_Component>(this, args...)));
		return GetComponent<T_Component>();
	}

	// Marks the component specified by the template argument type for deletion, along with all the components dependent on it.
	template<typename T_Component>
	bool GameObject::RemoveComponent()
	{
		if(typeid(T_Component) == typeid(TransformComponent))
		{
			std::cout << "Removing the transform of a GameObject is not allowed!\n";
			return false;
		}

		const auto type{ std::type_index{typeid(T_Component)} };
		if(auto pComponent{ GetComponent<T_Component>() })
		{
			RemoveDependentComponents(pComponent);
			m_pComponentTypesToDelete.push_back(type);
			return true;
		}
		
		return false;
	}

	// Automatically adds a component of the type specified by the template argument to the GameObject
	// if it is not found on the GameObject yet. Depending on the aforementioned, either returns the
	// existing or the newly created component.
	//
	// SHOULD ALWAYS BE FOLLOWED BY ADDING COMPONENT IN WHICH IT IS CALLED TO THE LIST OF DEPENDENTS OF THE REQUIRED COMPONENT
	// Use: "pRequiredComponent->AddDependentComponentType(&typeid(*this));"
	template<typename T_Component, typename... Args, typename>
	T_Component* GameObject::RequireComponent(Args... args)
	{
		const auto type{ std::type_index{typeid(T_Component)} };
		if(m_pComponents.contains(type))
		{
			return static_cast<T_Component*>(m_pComponents[type].get());
		}
		std::cout << "Automatically attaching " << type.name() << " to object!\n";
		return AddComponent<T_Component>(args...);
	}
}
#endif