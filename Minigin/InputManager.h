#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Singleton.h"
#include "Controller.h"
#include "Keyboard.h"
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

	struct ButtonAction
	{
		explicit ButtonAction() = default;
		explicit ButtonAction(int controllerID, int XInputGamepadButton, KeyState actionType)
			: m_ControllerID(controllerID)
			, m_XInputGamepadButton(XInputGamepadButton)
			, m_ActionType(actionType)
			, m_KeyboardButton(SDL_NUM_SCANCODES)
		{}
		explicit ButtonAction(int controllerID, SDL_Scancode keyboardButton, KeyState actionType)
			: m_ControllerID(controllerID)
			, m_XInputGamepadButton(0)
			, m_ActionType(actionType)
			, m_KeyboardButton(keyboardButton)
		{}
		int m_ControllerID;
		int m_XInputGamepadButton;
		SDL_Scancode m_KeyboardButton;
		KeyState m_ActionType;

		bool operator==(const ButtonAction& rhs) const
		{
			return m_XInputGamepadButton == rhs.m_XInputGamepadButton && m_ActionType == rhs.m_ActionType && m_ControllerID == rhs.m_ControllerID;
		}

		size_t operator()(const ButtonAction& keyValue) const
		{
			return	std::hash<int>()(keyValue.m_XInputGamepadButton)
				^ std::hash<int>()(static_cast<int>(keyValue.m_ActionType))
				^ std::hash<int>()(~static_cast<int>(keyValue.m_ControllerID))
				^ std::hash<int>()(~static_cast<int>(keyValue.m_KeyboardButton));
		}
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		bool ProcessInput();
		void BindCommand(const ButtonAction& buttonAction, Command* command);

	private:
		std::unique_ptr<Keyboard> m_pKeyboard;
		std::vector<std::unique_ptr<Command>> m_pDefinedCommands;
		std::unordered_map<ButtonAction, std::unique_ptr<Command>, ButtonAction> m_pCommandMap;
		std::vector<std::unique_ptr<Controller>> m_pControllers;

		void InitializeControllers();
		void UpdateControllers();
		void ProcessControllerActions();
	};

}
#endif