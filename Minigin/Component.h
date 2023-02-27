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
		Component() = default;
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(Component&& other) = delete;

		//virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

		void SetParentObject(GameObject* pParent) // TODO: don't use this, find alternative
		{
			m_pParentObject = pParent;
		}

	protected:
		// Todo: look into using shared_ptr instead
		GameObject* m_pParentObject;
	};
}
