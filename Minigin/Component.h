#ifndef COMPONENT_H
#define COMPONENT_H

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

		//virtual void Start() = 0;
		virtual void Update() = 0;

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
	};
}

#endif