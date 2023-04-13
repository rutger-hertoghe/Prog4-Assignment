#include "Subject.h"
#include "Observer.h"

void Subject::RegisterObserver(Observer* pObserver)
{
	m_pRegisteredObservers.push_back(pObserver);
}

void Subject::UnregisterObserver(Observer* pObserver)
{
	std::erase(m_pRegisteredObservers, pObserver);
}
