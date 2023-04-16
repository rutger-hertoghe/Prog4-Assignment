#include "SteamAchievementObserver.h"

#include "GameObject.h"
#include "ScoreComponent.h"
#include "SteamAchievements.h"

using namespace dae;

dae::SteamAchievementObserver::SteamAchievementObserver(std::initializer_list<ScoreComponent*> pScoreComponents)
{
	for(auto& pScoreComponent : pScoreComponents)
	{
		pScoreComponent->GetScoreChangeEvent()->RegisterObserver(this);
	}
}

void SteamAchievementObserver::Notify(GameObject* pGameObject)
{
	if (const auto playerScore{ pGameObject->GetComponent<ScoreComponent>() })
	{
		if(playerScore->GetScore() >= 500)
		{
			gSteamAchievements->SetAchievement("ACH_WIN_100_GAMES");
		}
	}
}
