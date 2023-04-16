#include "HealthObserver.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "TextComponent.h"

using namespace dae;

//TODO: much duplicate code of ScoreDisplayObserver, unify with inheritance/interface?

HealthDisplayObserver::HealthDisplayObserver(HealthComponent* pHealthComponent, GameObject* pUIElement)
	: m_pUIElement{pUIElement}
{
	pHealthComponent->GetHealthChangedEvent()->RegisterObserver(this);
}

void HealthDisplayObserver::Notify(GameObject* pGameObject)
{
	// TODO: specifically from here
	const auto pHealthComp{ pGameObject->GetComponent<HealthComponent>() };
	if(!pHealthComp)
	{
		std::cout << "HealthDisplayObserver: No health component found on " << pGameObject->GetName() << "!\n";
		return;
	}

	if(!m_pUIElement)
	{
		std::cout << "HealthDisplayObserver: Specified UI element does not exist!\n ";
		return;
	}

	const auto displayText{ m_pUIElement->GetComponent<TextComponent>() };
	if(!displayText)
	{
		std::cout << "HealthDisplayObserver: Specified UI element " << m_pUIElement->GetName() << " does not have a TextComponent!\n";
		return;
	}
	// to here

	const std::string newText{ "Lives: " + std::to_string(pHealthComp->GetHealth()) };
	displayText->SetText(newText);
}
