#include "TransformComponent.h"

using namespace dae;

TransformComponent::TransformComponent(GameObject* pParent)
	: Component(pParent)
	, m_HasChanged{ true }
{
	
}