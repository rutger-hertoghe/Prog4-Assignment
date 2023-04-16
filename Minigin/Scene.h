#ifndef SCENE_H
#define SCENE_H
#include "SceneManager.h"
#include "GameObject.h"
#include "Observer.h"
#include "Component.h"

namespace dae
{
	class Observer;
	//class GameObject;

	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<Observer>& pObserver);
		void Add(std::unique_ptr<GameObject>& pObject);
		// USE WITH CAUTION
		void Remove(GameObject* pObjToRemove);
		// USE WITH CAUTION
		void Remove(const std::string& objectName);
		void RemoveAll();

		void Update();
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector < std::unique_ptr<GameObject>> m_pObjects{};
		std::vector<std::unique_ptr<Observer>> m_pObservers{};
		std::vector<GameObject*> m_pObjectsToRemove{};

		static unsigned int m_idCounter;
	};

}
#endif