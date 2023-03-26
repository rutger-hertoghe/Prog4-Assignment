#include <SDL.h>
#include "InputManager.h"
//#include "Controller.h"
#include "imgui_impl_sdl2.h"

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <Xinput.h>

#include "Controller.h"
#include "Keyboard.h"

//#include "Command.h"


dae::InputManager::InputManager()
{
	InitializeInputDevices();

	constexpr int keyboardId{ 4 };
	m_pKeyboard = dynamic_cast<Keyboard*>(m_pInputDevices[keyboardId].get());
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			m_pKeyboard->SetDown(e.key.keysym.scancode);
		}
		if (e.type == SDL_KEYUP)
		{
			m_pKeyboard->SetUp(e.key.keysym.scancode);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		// IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	UpdateInputDevices();
	
	ProcessDeviceInput();

	return true;
}

void dae::InputManager::BindCommand(const ButtonAction& buttonAction, Command* command)
{
	m_pCommandMap.insert(std::make_pair(buttonAction, std::unique_ptr<Command>(command)));
}

void dae::InputManager::InitializeInputDevices()
{
	m_pInputDevices.resize(XUSER_MAX_COUNT + 1); // + 1 for keyboard

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		const DWORD dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS) // Bad name: "ERROR_SUCCESS" to indicate success
		{
			m_pInputDevices[static_cast<int>(i)] = std::make_unique<Controller>(i);
			// TODO: delete later
			std::cout << "Controller connected with ID " << i << "\n";
		}
	}
	m_pInputDevices[XUSER_MAX_COUNT] = std::make_unique<Keyboard>(XUSER_MAX_COUNT);
}

void dae::InputManager::UpdateInputDevices()
{
	for (const auto& pInputDevice : m_pInputDevices)
	{
		if (pInputDevice)
		{
			pInputDevice->Update();
		}
	}
}

void dae::InputManager::ProcessDeviceInput()
{
	for (const auto& buttonCommandPair : m_pCommandMap)
	{
		const auto& input{ buttonCommandPair.first };

		// TODO: Idea: remove all commands for unused input devices
		if (m_pInputDevices[input.m_InputDeviceID] == nullptr) continue; // If controller is not connected, but commands were specified, do not execute

		const auto& command{ buttonCommandPair.second };
		const int keyCode{ (input.m_IsGamePad ? input.m_XInputGamepadButton : input.m_KeyboardButton) };
		switch (input.m_ActionType)
		{
		case KeyState::down:
			if (m_pInputDevices[input.m_InputDeviceID]->IsDown(keyCode))
			{
				command->Execute();
			}
			break;
		case KeyState::pressed:
			if (m_pInputDevices[input.m_InputDeviceID]->IsPressed(keyCode))
			{
				command->Execute();
			}
			break;
		case KeyState::released:
			if (m_pInputDevices[input.m_InputDeviceID]->IsReleased(keyCode))
			{
				command->Execute();
			}
			break;
		}
	}
}
