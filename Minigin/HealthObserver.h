#ifndef HEALTH_DISPLAY_OBSERVER_H
#define HEALTH_DISPLAY_OBSERVER_H

#include "Observer.h"

namespace dae
{
	class HealthComponent;

	class HealthDisplayObserver final: public Observer
	{
	public:
		HealthDisplayObserver(HealthComponent* pHealthComponent, GameObject* pUIElement);
		void Notify(GameObject* pGameObject) override;

	private:
		GameObject* m_pUIElement;
	};
}

#endif