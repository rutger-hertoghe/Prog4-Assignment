#include "ScoreComponent.h"

using namespace dae;

ScoreComponent::ScoreComponent(GameObject* pGameObject)
	: Component{pGameObject}
	, m_pScoreChangeEvent{ std::make_unique<Subject>() }
	, m_Score{0}
{
}

void ScoreComponent::Update()
{
	// Do nothing
}

void ScoreComponent::ChangeScore(int amount)
{
	m_Score += amount;
	m_pScoreChangeEvent->NotifyObservers(GetGameObject());
}

int ScoreComponent::GetScore() const
{
	return m_Score;
}

Subject* ScoreComponent::GetScoreChangeEvent() const
{
	return m_pScoreChangeEvent.get();
}
