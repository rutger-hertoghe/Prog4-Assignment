#include "FPSCounterComponent.h"
#include "TextComponent.h"
#include <string>

#include "Time.h"

using namespace dae;

//class TextComponentNotFound{};

FPSCounterComponent::FPSCounterComponent(GameObject* pParent, float loggingRate)
	: Component(pParent)
	, m_TimePerLog(loggingRate)
	, m_pLinkedText(nullptr)
	, m_TimeSinceLastLog(0.f)
	, m_FramesSinceLastLog(0)
{
	m_pLinkedText = pParent->RequireComponent<TextComponent>();


	//m_pLinkedText = RequireComponent<TextComponent>();

	//m_pLinkedText = pParent->GetComponent<TextComponent>();
	//if (m_pLinkedText == nullptr)
	//{
	//	//std::cout << "Necessary text component not found! Automatically attaching TextComponent to object!\n";
	//	m_pLinkedText = pParent->AddComponent<TextComponent>(new TextComponent(pParent));
	//}
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
