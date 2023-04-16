#ifndef SCORE_DISPLAY_OBSERVER_H
#define SCORE_DISPLAY_OBSERVER_H

#include "Observer.h"

namespace dae
{
	class ScoreComponent;

	class ScoreDisplayObserver final : public Observer
	{
	public:
		ScoreDisplayObserver(ScoreComponent* pScoreComponent, GameObject* pUIElement);
		void Notify(GameObject* pGameObject) override;

	private:
		GameObject* m_pUIElement;
	};
}

#endif