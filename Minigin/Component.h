#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeindex>
#include <vector>

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		// Component constructor is in the protected field
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update() = 0;

		void AddDependentComponentType(std::type_index pDependentType)
		{
			m_pDependentComponentTypes.push_back(pDependentType);
		}

		[[nodiscard]] const std::vector<std::type_index>& GetDependentComponentTypes()
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

		std::vector<std::type_index> m_pDependentComponentTypes;
	};
}

#endif