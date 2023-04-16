#include "ScoreDisplayObserver.h"

#include "GameObject.h"
#include "ScoreComponent.h"
#include "TextComponent.h"

using namespace dae;

dae::ScoreDisplayObserver::ScoreDisplayObserver(ScoreComponent* pScoreComponent, GameObject* pUIElement)
	: m_pUIElement{pUIElement}
{
	pScoreComponent->GetScoreChangeEvent()->RegisterObserver(this);
}

void ScoreDisplayObserver::Notify(GameObject* pGameObject)
{
	const auto pScoreComponent{ pGameObject->GetComponent<ScoreComponent>() };
	if(!pScoreComponent)
	{
		std::cout << "ScoreDisplayObserver: No ScoreComponent found on " << pGameObject->GetName() << "!\n";
		return;
	}

	if(!m_pUIElement)
	{
		std::cout << "ScoreDisplayObserver: Specified UI element does not exist!\n";
		return;
	}

	const auto displayText{ m_pUIElement->GetComponent<TextComponent>() };
	if(!displayText)
	{
		std::cout << "ScoreDisplayObserver: Specified UI element " << m_pUIElement->GetName() << " does not have a TextComponent!\n";
		return;
	}

	const std::string newText{ "Score: " + std::to_string(pScoreComponent->GetScore()) };
	displayText->SetText(newText);
}
