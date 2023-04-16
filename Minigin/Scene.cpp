#include "Scene.h"
#include "GameObject.h"
#include "Component.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name)
	: m_Name{ name }
{
}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject>& pObject)
{
	m_pObjects.emplace_back(std::move(pObject));
}

void Scene::Add(std::unique_ptr<Observer>& pObserver)
{
	m_pObservers.emplace_back(std::move(pObserver));
}


void dae::Scene::Remove(GameObject* pObjToRemove)
{
	std::erase_if(m_pObjects, [pObjToRemove](const std::unique_ptr<GameObject>& pObjInScene)
		{
			return pObjInScene.get() == pObjToRemove;
		});
}

void dae::Scene::Remove(const std::string& objectName)
{
	std::erase_if(m_pObjects, [&objectName](const std::unique_ptr<GameObject>& pObject)
		{
			return pObject->GetName() == objectName;
		});
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void Scene::Update()
{
	// TODO: is inefficient right now, optimize this later (maybe make these separate functions?)
	for(auto& pObject : m_pObjects)
	{
		pObject->Update();
		if(pObject->IsMarkedForDestroy())
		{
			m_pObjectsToRemove.push_back(pObject.get());
		}
	}

	for(const auto& pDestroyedObject : m_pObjectsToRemove)
	{
		Remove(pDestroyedObject);
	}
}

void Scene::Render() const
{
	for (const auto& pObject : m_pObjects)
	{
		pObject->Render();
	}
}

