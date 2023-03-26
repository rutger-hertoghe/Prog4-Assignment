#include "Controller.h"

#include <iostream>


dae::Controller::Controller(DWORD id)
	: m_ControllerID(id)
	, m_ButtonsPressedThisFrame(0)
	, m_ButtonsReleasedThisFrame(0)
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}

void dae::Controller::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	// When both are XINPUT_STATES, the below does essentially the same, but might (keyword might) cause more overhead due to copy constuctor/assignment
	//m_PreviousState = m_CurrentState;
	XInputGetState(m_ControllerID, &m_CurrentState);

	const auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool dae::Controller::IsDown(int XInputGamepadButton) const
{
	return XInputGamepadButton & m_CurrentState.Gamepad.wButtons;
}

bool dae::Controller::IsReleased(int XInputGamepadButton) const
{
	return XInputGamepadButton & m_ButtonsReleasedThisFrame;
}

bool dae::Controller::IsPressed(int XInputGamepadButton) const
{
	return XInputGamepadButton & m_ButtonsPressedThisFrame;
}
