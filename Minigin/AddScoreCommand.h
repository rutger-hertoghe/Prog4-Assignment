#ifndef ADD_SCORE_COMMAND_H
#define ADD_SCORE_COMMAND_H

#include "Command.h"
namespace dae
{
	class ScoreComponent;

	class AddScoreCommand final : public Command
	{
	public:
		AddScoreCommand(GameObject* pGameObject, int amount);
		~AddScoreCommand() override = default;

		AddScoreCommand(const AddScoreCommand& other) = default;
		AddScoreCommand(AddScoreCommand&& other) = default;
		AddScoreCommand& operator=(const AddScoreCommand& other) = delete;
		AddScoreCommand& operator=(AddScoreCommand&& other) = delete;

		virtual void Execute() override;

	private:
		int m_ScoreAmount;
		ScoreComponent* m_ActorScore;
	};
}
#endif