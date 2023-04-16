#ifndef DAMAGE_COMMAND_H
#define DAMAGE_COMMAND_H

#include "Command.h"

namespace dae
{
	class HealthComponent;

	class DamageCommand final : public Command
	{
	public:
		DamageCommand(GameObject* pGameObject, int amount);
		~DamageCommand() override = default;

		DamageCommand(const DamageCommand& other) = default;
		DamageCommand& operator=(const DamageCommand& other) = delete;
		DamageCommand(DamageCommand&& other) = default;
		DamageCommand& operator=(DamageCommand&& other) = delete;

		virtual void Execute() override;

	private:
		int m_DamageAmount;
		HealthComponent* m_ActorHealth;
	};
}

#endif