#pragma once
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
		Component(Component&& other) = delete;
		Component& operator=(Component&& other) = delete;

		//virtual void Start() = 0;
		virtual void Update() = 0;

	protected:
		explicit Component(GameObject* pParent)
			: m_pParentObject(pParent)
		{}

		[[nodiscard]] GameObject* GetOwner() const
		{
			return m_pParentObject;
		}

	private:
		GameObject* m_pParentObject;
	};
}
