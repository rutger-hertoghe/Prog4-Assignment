#ifndef FPSCOUNTER_COMPONENT_H
#define FPSCOUNTER_COMPONENT_H

#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPSCounterComponent final : public Component
	{
	public:
		explicit FPSCounterComponent(GameObject* pGameObject, float loggingRate);
		~FPSCounterComponent() override = default;

		FPSCounterComponent(const FPSCounterComponent& other) = delete;
		FPSCounterComponent& operator=(const FPSCounterComponent& other) = delete;
		FPSCounterComponent(FPSCounterComponent&& other) = delete;
		FPSCounterComponent& operator=(FPSCounterComponent&& other) = delete;

		void Update() override;

	private:
		const float m_TimePerLog;
		float m_TimeSinceLastLog;
		int m_FramesSinceLastLog;

		TextComponent* m_pTextComponent;
	};

}
#endif