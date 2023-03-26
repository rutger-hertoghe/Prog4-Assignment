#ifndef COMMAND_H
#define COMMAND_H

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		Command(GameObject* pActor);
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;

	protected:
		[[nodiscard]] GameObject* GetActor() const;

	private:
		GameObject* m_pActor;
	};
}
#endif