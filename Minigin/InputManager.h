#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Singleton.h"
#include "Controller.h"
#include "Command.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace dae
{
	enum class KeyState
	{
		pressed,
		released,
		down
	};

	struct ControllerButtonAction
	{
		int controllerID;
		int XInputGamepadButton;
		KeyState actionType;

		bool operator==(const ControllerButtonAction& rhs) const
		{
			return XInputGamepadButton == rhs.XInputGamepadButton && actionType == rhs.actionType && controllerID == rhs.controllerID;
		}

		size_t operator()(const ControllerButtonAction& keyValue) const
		{
			return	std::hash<int>()(keyValue.XInputGamepadButton)
					^ std::hash<int>()(static_cast<int>(keyValue.actionType))
					^ std::hash<int>()(~static_cast<int>(keyValue.controllerID));
		}
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool ProcessInput();
		void BindCommand(const ControllerButtonAction& controllerButtonAction, Command* command);

	private:
		std::vector<std::unique_ptr<Command>> m_pDefinedCommands;
		std::unordered_map<ControllerButtonAction, std::unique_ptr<Command>, ControllerButtonAction> m_pCommandMap;
		std::vector<std::unique_ptr<Controller>> m_pControllers;
		//void BindCommand(const ControllerButtonAction& controllerButtonAction, Command* command);

		void InitializeControllers();
	};

}
#endif