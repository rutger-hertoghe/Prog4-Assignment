#ifndef COMMAND_H
#define COMMAND_H

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		// Command constructor is in protected field
		virtual ~Command() = default;

		Command(const Command& other) = default;
		Command& operator=(const Command& other) = delete;
		Command(Command&& other) = default;
		Command& operator=(Command&& other) = delete;

		virtual void Execute() = 0;

	protected:
		explicit Command(GameObject* pActor);
		[[nodiscard]] GameObject* GetActor() const;

	private:
		GameObject* m_pActor;
	};
}
#endif