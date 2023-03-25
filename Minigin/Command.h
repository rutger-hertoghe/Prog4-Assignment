#ifndef COMMAND_H
#define COMMAND_H

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;

	protected:

	private:
		GameObject* m_pGameActor;
	};

	class MoveOnXCommand final : public Command
	{
	public:
		virtual void Execute() override;

	private:
	};

}
#endif