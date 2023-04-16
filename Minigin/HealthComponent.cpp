#include "HealthComponent.h"

#include <iostream>

#include "GameObject.h"

using namespace dae;

HealthComponent::HealthComponent(GameObject* pGameObject, int maxHealth)
	: Component{pGameObject}
	, m_MaxHealth{maxHealth}
	, m_CurrentHealth{maxHealth}
{
	if(m_MaxHealth <= 0)
	{
		// TODO: add name member (std::string) to GameObjects to be able to trace for which object problems occur.
		std::cout << "Max health value given to GameObject \"" << pGameObject->GetName() << "\" was below zero!\n"
			<< "Max health was set to 0, GameObject will be considered dead\n";
	}
}

void HealthComponent::Update()
{
	// Do nothing
}

void HealthComponent::Damage(int amount)
{
	ChangeHealth(-amount);
}

void dae::HealthComponent::Heal(int amount)
{
	ChangeHealth(amount);
}

void HealthComponent::ChangeHealth(int amount)
{
	m_CurrentHealth += amount;
	if(m_CurrentHealth <= 0)
	{
		m_CurrentHealth = 0;
		m_pDeathEvent->NotifyObservers(GetGameObject());
		return;
	}

	if(m_CurrentHealth > m_MaxHealth)
	{
		m_CurrentHealth = m_MaxHealth;
	}
}
