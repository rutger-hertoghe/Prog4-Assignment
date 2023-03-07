#pragma once
#include "Component.h"
namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		explicit TransformComponent(GameObject* pParent);
		// TODO: prototype this straight on the gameobject before moving all this here

	private:
		bool m_HasChanged;
	};
}


