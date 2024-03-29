#include "FPSCounterComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Time.h"

#include <string>

using namespace dae;

FPSCounterComponent::FPSCounterComponent(GameObject* pGameObject, float loggingRate)
	: Component(pGameObject)
	, m_TimePerLog(loggingRate)
	, m_TimeSinceLastLog(0.f)
	, m_FramesSinceLastLog(0)
{
	m_pTextComponent = pGameObject->RequireComponent<TextComponent>();
	m_pTextComponent->AddDependentComponentType(&typeid(*this));
}

void FPSCounterComponent::Update()
{
	++m_FramesSinceLastLog;
	m_TimeSinceLastLog += Time::GetInstance().GetElapsed();

	if (m_TimeSinceLastLog < m_TimePerLog) return;
	
	const int fps{ static_cast<int>(static_cast<float>(m_FramesSinceLastLog) / m_TimePerLog) };
	if (m_pTextComponent)
	{
		m_pTextComponent->SetText(std::to_string(fps) + "FPS");
	}
	m_TimeSinceLastLog = 0.f;
	m_FramesSinceLastLog = 0;
	
}
