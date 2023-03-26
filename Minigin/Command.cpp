#include "Command.h"
#include "GameObject.h"

using namespace dae;

Command::Command(GameObject* pActor)
	: m_pActor(pActor)
{
}

GameObject* Command::GetActor() const
{
	return m_pActor;
}
