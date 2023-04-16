#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

namespace dae
{
	class Observer;
	class GameObject;

	class Subject final
	{
	public:
		Subject() = default;

		void RegisterObserver(Observer* pObserver);
		void UnregisterObserver(Observer* pObserver);
		void NotifyObservers(GameObject* pGameObject) const;

	private:
		std::vector<Observer*> m_pRegisteredObservers;
	};
}

#endif