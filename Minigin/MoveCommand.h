#ifndef MOVE_COMMAND_H
#define MOVE_COMMAND_H

#include <glm/vec3.hpp>

#include "Command.h"

namespace dae
{
    class MoveCommand final : public Command
    {
    public:
        MoveCommand(GameObject* pActor, const glm::vec3& direction);

        // TODO: implement execution of MoveCommand
        void Execute() override;

    private:
        glm::vec3 m_Direction;
    };
}
#endif