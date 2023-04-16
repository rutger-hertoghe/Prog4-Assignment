#ifndef SCORE_COMPONENT_H
#define SCORE_COMPONENT_H

#include <memory>

#include "Component.h"
#include "Subject.h"
namespace dae
{
	class ScoreComponent final : public Component
	{
	public:
		ScoreComponent(GameObject* pGameObject);
		~ScoreComponent() override = default;

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void Update() override;

		void ChangeScore(int amount);
		[[nodiscard]] int GetScore() const;

		[[nodiscard]] Subject* GetScoreChangeEvent() const;

	private:
		int m_Score;

		std::unique_ptr<Subject> m_pScoreChangeEvent;
	};
}

#endif