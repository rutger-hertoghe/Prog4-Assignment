#include "FPSCounterComponent.h"
#include "TextComponent.h"
#include <string>

#include "Time.h"

using namespace dae;

class TextComponentNotFound{};

FPSCounterComponent::FPSCounterComponent(float loggingRate)
	: m_TimePerLog(loggingRate)
	, m_pLinkedText(nullptr)
	, m_TimeSinceLastLog(0.f)
	, m_FramesSinceLastLog(0)
{
}

//void FPSCounterComponent::Start()
//{
//	m_pLinkedText = m_pParentObject->GetComponent<dae::TextComponent>();
//	if(m_pLinkedText == nullptr)
//	{
//		std::cerr << "Necessary text component not found!\n";
//		throw TextComponentNotFound();
//	}
//}

void FPSCounterComponent::Render()
{
	// Nothing to render
}

void FPSCounterComponent::Update()
{
	if(m_pLinkedText == nullptr)
	{
		m_pLinkedText = m_pParentObject->GetComponent<TextComponent>();
		if(m_pLinkedText == nullptr)
		{
			std::cerr << "Necessary text component not found!\n";
			throw TextComponentNotFound();
		}
	}

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
