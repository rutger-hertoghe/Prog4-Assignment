#include "Controller.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>

using namespace dae;

class Controller::ControllerImplementation final
{
public:
	ControllerImplementation(unsigned int id);
	void Update();

	[[nodiscard]] bool IsDown(int XInputGamepadButton) const;
	[[nodiscard]] bool IsReleased(int XInputGamepadButton) const;
	[[nodiscard]] bool IsPressed(int XInputGamepadButton) const;

private:
	unsigned int m_DeviceID;
	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;

	int m_ButtonsPressedThisFrame;
	int m_ButtonsReleasedThisFrame;
};

dae::Controller::Controller(unsigned int id)
	: InputDevice(id)
{
	m_pImpl = std::make_unique<ControllerImplementation>(id);
}

// Located here, because smart_ptr otherwise determines Implementation to be incomplete
dae::Controller::~Controller() = default;

void dae::Controller::Update()
{
	m_pImpl->Update();
}

bool dae::Controller::IsDown(int XInputGamepadButton) const
{
	return m_pImpl->IsDown(XInputGamepadButton);
}

bool dae::Controller::IsPressed(int XInputGamepadButton) const
{
	return m_pImpl->IsPressed(XInputGamepadButton);
}

bool dae::Controller::IsReleased(int XInputGamepadButton) const
{
	return m_pImpl->IsReleased(XInputGamepadButton);
}

Controller::ControllerImplementation::ControllerImplementation(unsigned int id)
	: m_DeviceID(id)
	, m_ButtonsPressedThisFrame(0)
	, m_ButtonsReleasedThisFrame(0)
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}

void Controller::ControllerImplementation::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	// When both are XINPUT_STATES, the below does essentially the same, but might (keyword might) cause more overhead due to copy constuctor/assignment
	//m_PreviousState = m_CurrentState;
	XInputGetState(m_DeviceID, &m_CurrentState);

	const auto buttonChanges{ m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool Controller::ControllerImplementation::IsDown(int XInputGamepadButton) const
{
	return XInputGamepadButton & m_CurrentState.Gamepad.wButtons;
}

bool Controller::ControllerImplementation::IsReleased(int XInputGamepadButton) const
{
	return XInputGamepadButton & m_ButtonsReleasedThisFrame;
}

bool Controller::ControllerImplementation::IsPressed(int XInputGamepadButton) const
{
	return XInputGamepadButton & m_ButtonsPressedThisFrame;
}