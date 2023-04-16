#include "Subject.h"
#include "Observer.h"
#include "GameObject.h"

using namespace dae;

void Subject::RegisterObserver(Observer* pObserver)
{
	m_pRegisteredObservers.push_back(pObserver);
}

void Subject::UnregisterObserver(Observer* pObserver)
{
	std::erase(m_pRegisteredObservers, pObserver);
}

void Subject::NotifyObservers(GameObject* pGameObject) const
{
	for(const auto pObserver : m_pRegisteredObservers)
	{
		pObserver->Notify(pGameObject);
	}
}
