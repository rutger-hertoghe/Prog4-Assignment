#include "MoveCommand.h"

#include <iostream>

using namespace dae;

MoveCommand::MoveCommand(GameObject* pActor, const glm::vec3& direction)
	: Command(pActor)
	, m_Direction(direction)
{
}

void dae::MoveCommand::Execute()
{
	std::cout << "Moving!\n";
}
