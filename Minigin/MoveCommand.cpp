#include "MoveCommand.h"

#include <iostream>

#include "GameObject.h"
#include "MovementBehaviorComponent.h"

using namespace dae;

MoveCommand::MoveCommand(GameObject* pActor, const glm::vec2& direction)
	: Command(pActor)
	, m_Direction(direction)
{
	m_MovementBehaviorComponent = pActor->GetComponent<MovementBehaviorComponent>();
	if(!m_MovementBehaviorComponent)
	{
		std::cout << "MoveCommand was attached to GameObject without MovementBehaviorComponent!\n"
				  << "If you intend to bind a MoveCommand to a GameObject, add the component first\n";
	}
}

void dae::MoveCommand::Execute()
{
	if(m_MovementBehaviorComponent)
	{
		m_MovementBehaviorComponent->AddMovementInDirection(m_Direction);
	}
}
