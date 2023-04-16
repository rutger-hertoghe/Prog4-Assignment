#ifndef STEAM_ACHIEVEMENT_OBSERVER_H
#define STEAM_ACHIEVEMENT_OBSERVER_H

#include <initializer_list>

#include "Observer.h"

namespace dae
{
	class ScoreComponent;

	class SteamAchievementObserver final : public Observer
	{
	public:
		SteamAchievementObserver(std::initializer_list<ScoreComponent*> pScoreComponents);
		void Notify(GameObject* pGameObject) override;
	};
}

#endif