#ifndef OBSERVER_H
#define OBSERVER_H

namespace dae
{
	class GameObject;

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(GameObject* pGameObject) = 0;
	};
}
#endif