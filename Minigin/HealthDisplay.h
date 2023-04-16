#ifndef HEALTH_DISPLAY_H
#define HEALTH_DISPLAY_H

#include "Observer.h"

namespace dae
{
	class HealthDisplay final : public Observer
	{
	public:
		HealthDisplay();
		void Notify(GameObject* pGameObject) override;

	private:
		int m_Lives;
	};
}
#endif