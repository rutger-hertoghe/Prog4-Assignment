#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Singleton.h"
#include "InputDevice.h"
#include "Command.h"

#include <memory>
#include <unordered_map>
#include <vector>

#include "Controller.h"

namespace dae
{
	class Keyboard;

	enum class KeyState
	{
		pressed,
		released,
		down
	};

	struct ButtonAction
	{
		explicit ButtonAction() = default;
		explicit ButtonAction(int controllerID, GamePad button, KeyState actionType)
			: m_InputDeviceID(controllerID)
			, m_XInputGamepadButton(static_cast<int>(button))
			, m_ActionType(actionType)
			, m_KeyboardButton(SDL_NUM_SCANCODES)
			, m_IsGamePad(true)
		{}
		explicit ButtonAction(SDL_Scancode keyboardButton, KeyState actionType)
			: m_InputDeviceID(4) // Always 4 for keyboard
			, m_XInputGamepadButton(0)
			, m_ActionType(actionType)
			, m_KeyboardButton(keyboardButton)
			, m_IsGamePad(false)
		{}
		int m_InputDeviceID;
		int m_XInputGamepadButton;
		SDL_Scancode m_KeyboardButton;
		KeyState m_ActionType;

		bool m_IsGamePad;

		bool operator==(const ButtonAction& rhs) const
		{
			return m_XInputGamepadButton == rhs.m_XInputGamepadButton && m_ActionType == rhs.m_ActionType && m_InputDeviceID == rhs.m_InputDeviceID;
		}

		size_t operator()(const ButtonAction& keyValue) const
		{
			// TODO: work with regular map, hash could fail
			return	std::hash<int>()(keyValue.m_XInputGamepadButton)
				^ std::hash<int>()(static_cast<int>(keyValue.m_ActionType))
				^ std::hash<int>()(~static_cast<int>(keyValue.m_InputDeviceID))
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
		Keyboard* m_pKeyboard; // Raw pointer for easy access
		std::vector<std::unique_ptr<Command>> m_pDefinedCommands;
		std::unordered_map<ButtonAction, std::unique_ptr<Command>, ButtonAction> m_pCommandMap;
		std::vector<std::unique_ptr<InputDevice>> m_pInputDevices;

		void InitializeInputDevices();
		void UpdateInputDevices();
		void ProcessDeviceInput();
		bool ProcessSDLEvents();
	};

}
#endif