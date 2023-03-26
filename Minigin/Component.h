#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update() = 0;

		void AddDependentComponentType(const type_info* pDependentType)
		{
			m_pDependentComponentTypes.push_back(pDependentType);
		}

		[[nodiscard]] const std::vector<const type_info*>& GetDependentComponentTypes()
		{
			return m_pDependentComponentTypes;
		}

	protected:
		explicit Component(GameObject* pGameObject)
			: m_pGameObject(pGameObject)
		{}

		[[nodiscard]] GameObject* GetGameObject() const
		{
			return m_pGameObject;
		}

	private:
		GameObject* m_pGameObject;

		std::vector<const type_info*> m_pDependentComponentTypes;
	};
}

#endif