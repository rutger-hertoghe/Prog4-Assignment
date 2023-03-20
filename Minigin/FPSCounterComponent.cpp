#include "FPSCounterComponent.h"
#include "TextComponent.h"
#include <string>

#include "Time.h"

using namespace dae;

//class TextComponentNotFound{};

FPSCounterComponent::FPSCounterComponent(GameObject* pGameObject, float loggingRate)
	: Component(pGameObject)
	, m_TimePerLog(loggingRate)
	, m_pLinkedText(nullptr)
	, m_TimeSinceLastLog(0.f)
	, m_FramesSinceLastLog(0)
{
	m_pLinkedText = pGameObject->RequireComponent<TextComponent>();
}

void FPSCounterComponent::Update()
{
	++m_FramesSinceLastLog;
	m_TimeSinceLastLog += Time::GetInstance().GetElapsed();

	if(m_TimeSinceLastLog > m_TimePerLog)
	{
		const int fps{ static_cast<int>(static_cast<float>(m_FramesSinceLastLog) / m_TimePerLog) };
		m_pLinkedText->SetText(std::to_string(fps) + " FPS");
		m_TimeSinceLastLog = 0.f;
		m_FramesSinceLastLog = 0;
	}
}
