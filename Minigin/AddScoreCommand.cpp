#include "AddScoreCommand.h"

#include "GameObject.h"
#include "ScoreComponent.h"

using namespace dae;

AddScoreCommand::AddScoreCommand(GameObject* pGameObject, int amount)
	: Command{ pGameObject }
	, m_ScoreAmount{ amount }
{
	m_ActorScore = pGameObject->GetComponent<ScoreComponent>();
	if(!m_ActorScore)
	{
		std::cout << "AddScoreCommand: GameObject \"" << pGameObject->GetName() << "\" does not have a ScoreComponent!\n"
			<< "AddScore commands will not work!\n";
	}
}

void dae::AddScoreCommand::Execute()
{
	if(m_ActorScore)
	{
		m_ActorScore->ChangeScore(m_ScoreAmount);
	}
}
