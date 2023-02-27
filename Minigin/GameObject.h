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
	class Texture2D;
	class Component;

	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetPosition(float x, float y);
		const Transform& GetTransform() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename T_Component>
		T_Component* GetComponent();

		template<typename T_Component>
		void AddComponent(Component* pComponent);

		template<typename T_Component>
		bool RemoveComponent();

	private:
		Transform m_transform{};
		TypeMap<Component*> m_pComponents;
		void SetComponentParent(Component* pComponent);
	};

	template <typename T_Component>
	T_Component* GameObject::GetComponent()
	{
		try
		{
			auto pComponent{ m_pComponents.at<T_Component>() };
			return static_cast<T_Component*>(pComponent);
		}
		catch(TypeNotInMapException&)
		{
			std::cerr << "GameObject does not have specified component attached!\n";
			return nullptr;
		}
	}

	template<typename T_Component>
	void GameObject::AddComponent(Component * pComponent)
	{
		SetComponentParent(pComponent);
		m_pComponents.emplace<T_Component>(pComponent);
	}

	template<typename T_Component>
	bool GameObject::RemoveComponent()
	{
		auto pComponent = GetComponent<T_Component>();
		if (pComponent == nullptr) return false;

		delete pComponent;

		return m_pComponents.erase<T_Component>();
	}	
}
