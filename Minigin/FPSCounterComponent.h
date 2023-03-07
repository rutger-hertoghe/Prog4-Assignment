#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPSCounterComponent final : public Component
	{
	public:
		explicit FPSCounterComponent(GameObject* pParent, float loggingRate);
		virtual ~FPSCounterComponent() override = default;

		FPSCounterComponent(const FPSCounterComponent& other) = delete;
		FPSCounterComponent& operator=(const FPSCounterComponent& other) = delete;
		FPSCounterComponent(FPSCounterComponent&& other) = delete;
		FPSCounterComponent& operator=(FPSCounterComponent&& other) = delete;

		void Update() override;

	private:
		TextComponent* m_pLinkedText;

		const float m_TimePerLog;
		float m_TimeSinceLastLog;
		int m_FramesSinceLastLog;
	};

}
