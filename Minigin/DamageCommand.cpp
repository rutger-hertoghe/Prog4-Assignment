#include "DamageCommand.h"

#include "GameObject.h"
#include "HealthComponent.h"

using namespace dae;

DamageCommand::DamageCommand(GameObject* pGameObject, int amount)
	: Command{pGameObject}
	, m_DamageAmount{amount}
{
	m_ActorHealth = pGameObject->GetComponent<HealthComponent>();
	if(!m_ActorHealth)
	{
		std::cout << "DamageCommand: GameObject \"" << pGameObject->GetName() << "\" does not have a HealthComponent!\n"
			<< "Damage commands will not work!\n";
	}
}

void dae::DamageCommand::Execute()
{
	if(m_ActorHealth)
	{
		m_ActorHealth->Damage(m_DamageAmount);
	}
}
