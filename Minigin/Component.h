#pragma once
#include <memory>
#include <string>

#include "GameObject.h"

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component(Component&& other) noexcept
		{
			m_pParentObject = other.m_pParentObject;
			other.m_pParentObject = nullptr;
		}
		Component& operator=(Component&& other)
		{
			m_pParentObject = other.m_pParentObject;
			other.m_pParentObject = nullptr;
			return *this;
		}

		//virtual void Start() = 0;
		virtual void Update() = 0;

	protected:
		explicit Component(GameObject* pParent)
			: m_pParentObject(pParent)
		{}

		[[nodiscard]] GameObject* GetParentObject() const
		{
			return m_pParentObject;
		}

	private:
		GameObject* m_pParentObject;
	};
}
