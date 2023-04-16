#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include <memory>

#include "Component.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent final : public Component
	{
	public:
		HealthComponent(GameObject* pGameObject, int maxHealth);
		~HealthComponent() override = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		virtual void Update() override;

		void Damage(int amount);
		void Heal(int amount);

		[[nodiscard]] int GetHealth() const;
		[[nodiscard]] int GetMaxHealth() const;

		[[nodiscard]] Subject* GetDeathEvent() const;
		[[nodiscard]] Subject* GetHealthChangedEvent() const;

	private:
		int m_MaxHealth;
		int m_CurrentHealth;

		std::unique_ptr<Subject> m_pDeathEvent;
		std::unique_ptr<Subject> m_pHealthChangedEvent;

		void ChangeHealth(int amount);
	};
}
#endif