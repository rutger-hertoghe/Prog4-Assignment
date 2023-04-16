#include "HealthComponent.h"

#include <iostream>

#include "GameObject.h"

using namespace dae;

HealthComponent::HealthComponent(GameObject* pGameObject, int maxHealth)
	: Component{pGameObject}
	, m_MaxHealth{maxHealth}
	, m_CurrentHealth{maxHealth}
	, m_pDeathEvent{ std::make_unique<Subject>() }
	, m_pHealthChangedEvent{ std::make_unique<Subject>() }
{
	if(m_MaxHealth <= 0)
	{
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

int dae::HealthComponent::GetHealth() const
{
	return m_CurrentHealth;
}

int dae::HealthComponent::GetMaxHealth() const
{
	return m_MaxHealth;
}

Subject* dae::HealthComponent::GetDeathEvent() const
{
	return m_pDeathEvent.get();
}

Subject* dae::HealthComponent::GetHealthChangedEvent() const
{
	return m_pHealthChangedEvent.get();
}

void HealthComponent::ChangeHealth(int amount)
{
	m_CurrentHealth += amount;
	m_pHealthChangedEvent->NotifyObservers(GetGameObject());

	if(m_CurrentHealth <= 0)
	{
		m_CurrentHealth = 0;
		m_pDeathEvent->NotifyObservers(GetGameObject());
		m_pHealthChangedEvent->NotifyObservers(GetGameObject());
		return;
	}
	
	if(m_CurrentHealth > m_MaxHealth)
	{
		m_CurrentHealth = m_MaxHealth;
	}
}
