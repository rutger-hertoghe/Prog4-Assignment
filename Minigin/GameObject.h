#pragma once
#include <memory>
#include <string>
#include "TypeMap.h"
#include <stdexcept>
#include <iostream>
#include "Component.h"

#include "Transform.h"

namespace dae
{
	using namespace std;
	class Texture2D;
	class Component;

	class GameObject final : public std::enable_shared_from_this<GameObject> // inherit to enable 'shared_from_this' to set children
	{
	public:
		// BIG SIX
		GameObject() = default;
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// GAMELOOP FUNCTIONS
		void Update();
		void Render(); //const;

		void SetPosition(float x, float y);
		[[nodiscard]] const Transform& GetLocalTransform() const;
		[[nodiscard]] const Transform& GetWorldTransform() const;

		// COMPONENTS
		template<typename T_Component>
		T_Component* GetComponent(); //const; // TODO: QUESTION why does setting const here break my code?

		// TODO: further look into this
		//// std::is_constructible_v<T_Component, Args...> checks if type 'T_Component' can be constructed from the arguments, if so, the function is enabled
		//template<typename T_Component, typename... Args, std::enable_if_t<std::is_constructible_v<T_Component, Args...>>>
		template<typename T_Component, typename... Args, typename = std::enable_if_t<std::is_constructible_v<T_Component, Args...>>>
		T_Component* AddComponent(Args... args);

		template<typename T_Component>
		bool RemoveComponent();

		template<typename T_Component>
		T_Component* RequireComponent();

		// PARENTING & CHILDRENING (?)
		[[nodiscard]] shared_ptr<GameObject> GetParent() const;
		void SetParent(const shared_ptr<GameObject>& pParentObj);

		[[nodiscard]] int GetChildCount() const;
		[[nodiscard]] shared_ptr<GameObject> GetChildAt(int idx);

	private:
		Transform m_LocalTransform{};
		Transform m_WorldTransform{};

		TypeMap<std::unique_ptr<Component>> m_pComponents;

		shared_ptr<GameObject> m_pParent;
		// TODO: why shared_ptr's here? Now children are shared with scene, but could be handled within gameObjects?
		vector<shared_ptr<GameObject>> m_pChildren;

		void AddChild(const shared_ptr<GameObject>& pChild);
		void RemoveChild(const shared_ptr<GameObject>& pChild);
	};



	// |--------------------------------|
	// | TEMPLATED FUNCTION DEFINITIONS |
	// |--------------------------------|

	template <typename T_Component>
	T_Component* GameObject::GetComponent() //const
	{
		// TODO: reimplement this
		/*try
		{
			auto pComponent{ m_pComponents.at<T_Component>() };
			return static_cast<T_Component*>(pComponent);
		}
		catch(TypeNotInMapException&)
		{
			std::cerr << "GameObject does not have specified component attached!\n";
			return nullptr;
		}*/
		return nullptr;
	}

	//template<typename T_Component>
	template<typename T_Component, typename... Args, typename>
	T_Component* GameObject::AddComponent(Args... args)
	{
		auto unqComponent = std::make_unique<T_Component>(args...);
		auto rawPtr = unqComponent.get();
		m_pComponents.emplace<T_Component>(std::move(unqComponent));
		return rawPtr;
	}

	/*template<typename T_Component>
	T_Component* GameObject::AddComponent(std::unique_ptr<T_Component> pComponent)
	{
		auto rawPtr = pComponent.get();
		m_pComponents.emplace<T_Component>(std::move(pComponent));
		return static_cast<T_Component*>(rawPtr);
	}*/

	template<typename T_Component>
	bool GameObject::RemoveComponent()
	{
		auto pComponent = GetComponent<T_Component>();
		if (pComponent == nullptr) return false;

		delete pComponent;

		return m_pComponents.erase<T_Component>();
	}

	template<typename T_Component>
	T_Component* GameObject::RequireComponent()
	{
		auto pRequiredComponent = GetComponent<T_Component>();
		if (pRequiredComponent == nullptr)
		{
			// TODO: remove because of cluttering & lack of clarity in console?
			std::cout << "Necessary text component not found! Automatically attaching " << typeid(T_Component).name() <<" to object!\n";
			// TODO: reenable this when AddComponent is in order
			//pRequiredComponent = AddComponent<T_Component>(new T_Component(this));
		}
		return pRequiredComponent;
	}
}
