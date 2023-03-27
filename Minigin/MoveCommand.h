#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <glm/vec2.hpp>

#include "Command.h"

namespace dae
{
    class MovementBehaviorComponent;

	class MoveCommand final : public Command
    {
    public:
        MoveCommand(GameObject* pActor, const glm::vec2& direction);
        virtual ~MoveCommand() override = default;

        MoveCommand(const MoveCommand& other) = default;
        MoveCommand& operator=(const MoveCommand& other) = delete;
        MoveCommand(MoveCommand&& other) = default;
        MoveCommand& operator=(MoveCommand&& other) = delete;

        void Execute() override;

    private:
        glm::vec2 m_Direction;
        MovementBehaviorComponent* m_MovementBehaviorComponent;
    };
}
#endif