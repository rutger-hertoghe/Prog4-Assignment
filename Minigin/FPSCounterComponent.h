#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPSCounterComponent : public Component
	{
	public:
		FPSCounterComponent() = delete;
		FPSCounterComponent(float loggingRate);


		void Render() override;
		void Update() override;

	private:
		TextComponent* m_pLinkedText;

		const float m_TimePerLog;
		float m_TimeSinceLastLog;
		int m_FramesSinceLastLog;
	};

}
