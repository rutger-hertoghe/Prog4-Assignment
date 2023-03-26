#include <SDL.h>
#include "InputManager.h"
//#include "Controller.h"
#include "imgui_impl_sdl2.h"

#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <windows.h>
#include <Xinput.h>

//#include "Command.h"


dae::InputManager::InputManager()
{
	InitializeControllers();

	m_pKeyboard = std::make_unique<Keyboard>(4);
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
	UpdateControllers();
	ProcessControllerActions();

	m_pKeyboard->Update();


	return true;
}

void dae::InputManager::BindCommand(const ButtonAction& buttonAction, Command* command)
{
	m_pCommandMap.insert(std::make_pair(buttonAction, std::unique_ptr<Command>(command)));
}

void dae::InputManager::InitializeControllers()
{
	m_pControllers.resize(XUSER_MAX_COUNT);

	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		const DWORD dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS) // Bad name: "ERROR_SUCCESS" to indicate success
		{
			m_pControllers[static_cast<int>(i)] = std::make_unique<Controller>(i);
			// TODO: delete later
			std::cout << "Controller connected with ID " << i << "\n";
		}
		//else
		//{
		//	m_pControllers.pop_back(); // To ensure the vector shrinks again for size correctness at a later point
		//}
	}
}

void dae::InputManager::UpdateControllers()
{
	for (const auto& controller : m_pControllers)
	{
		if (controller)
		{
			controller->Update();
		}
	}
}

void dae::InputManager::ProcessControllerActions()
{
	for (const auto& buttonCommandPair : m_pCommandMap)
	{
		switch (buttonCommandPair.first.m_ActionType)
		{
		case KeyState::down:
			if (m_pControllers[buttonCommandPair.first.m_ControllerID]->IsDown(buttonCommandPair.first.m_XInputGamepadButton))
			{
				buttonCommandPair.second->Execute();
			}
			break;
		case KeyState::pressed:
			if (m_pControllers[buttonCommandPair.first.m_ControllerID]->IsPressed(buttonCommandPair.first.m_XInputGamepadButton))
			{
				buttonCommandPair.second->Execute();
			}
			break;
		case KeyState::released:
			if (m_pControllers[buttonCommandPair.first.m_ControllerID]->IsReleased(buttonCommandPair.first.m_XInputGamepadButton))
			{
				buttonCommandPair.second->Execute();
			}
			break;
		}
	}
}
