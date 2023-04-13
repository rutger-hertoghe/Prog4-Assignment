#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject
{
public:
	void RegisterObserver(Observer* pObserver);
	void UnregisterObserver(Observer* pObserver);

protected:
	void NotifyObservers();

private:
	std::vector<Observer*> m_pRegisteredObservers;
};

#endif