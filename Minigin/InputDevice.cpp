#include "InputDevice.h"

#define WIN32_LEAN_AND_MEAN
#include <bitset>
#include <SDL_scancode.h>
#include <windows.h>
#include <Xinput.h>

using namespace dae;

// BASE: INPUT DEVICE IMPLEMENTATION
class InputDevice::InputDeviceImplementation
{
public:
	virtual void Update() = 0;
	virtual ~InputDeviceImplementation() = default;

	[[nodiscard]] virtual bool IsDown(int button) const = 0;
	[[nodiscard]] virtual bool IsReleased(int button) const = 0;
	[[nodiscard]] virtual bool IsPressed(int button) const = 0;

	virtual void SetDown(int button) = 0;
	virtual void SetUp(int button) = 0;
protected:
	InputDeviceImplementation(unsigned int id)
		: m_DeviceID{ static_cast<DWORD>(id) }
	{}

	DWORD m_DeviceID;
};

// DERIVED: CONTROLLER IMPLEMENTATION
class InputDevice::ControllerImplementation final : public InputDeviceImplementation
{
public:
	ControllerImplementation(unsigned int id);
	void Update() override;

	[[nodiscard]] virtual bool IsDown(int XInputGamepadButton) const override;
	[[nodiscard]] virtual bool IsReleased(int XInputGamepadButton) const override;
	[[nodiscard]] virtual bool IsPressed(int XInputGamepadButton) const override;

	//
	void SetDown(int XInputGamepadButton) override;
	virtual void SetUp(int XInputGamepadButton) override;
private:
	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;

	int m_ButtonsPressedThisFrame;
	int m_ButtonsReleasedThisFrame;
};

// DERIVED KEYBOARD IMPLEMENTATION
class InputDevice::KeyboardImplementation final : public InputDeviceImplementation
{
public:
	KeyboardImplementation(unsigned int id);

	void Update() override;
	[[nodiscard]] virtual bool IsDown(int SDL_Scancode) const override;
	[[nodiscard]] virtual bool IsPressed(int SDL_Scancode) const override;
	[[nodiscard]] virtual bool IsReleased(int SDL_Scancode) const override;

	virtual void SetDown(int SDL_ScanCode) override;
	virtual void SetUp(int SDL_ScanCode) override;
	
private:
	static constexpr int numScanCodes{ static_cast<int>(SDL_NUM_SCANCODES) };
	std::bitset<numScanCodes> m_CurrentState;
	std::bitset<numScanCodes> m_PreviousState;

	std::bitset<numScanCodes> m_KeysPressedThisFrame;
	std::bitset<numScanCodes> m_KeysReleasedThisFrame;
};

dae::InputDevice::InputDevice(unsigned int id, DeviceType deviceType)
	: pImpl(nullptr)
{
	switch(deviceType)
	{
	case DeviceType::Controller:
		pImpl = std::make_unique<ControllerImplementation>(id);
		break;
	case DeviceType::Keyboard:
		pImpl = std::make_unique<KeyboardImplementation>(id);
		break;
	}
}

dae::InputDevice::~InputDevice() = default;

void dae::InputDevice::Update()
{
	pImpl->Update();
}

bool dae::InputDevice::IsDown(int button) const
{
	return pImpl->IsDown(button);
}

bool dae::InputDevice::IsReleased(int button) const
{
	return pImpl->IsReleased(button);
}

bool dae::InputDevice::IsPressed(int button) const
{
	return pImpl->IsPressed(button);
}

void dae::InputDevice::SetDown(int button)
{
	pImpl->SetDown(button);
}

void dae::InputDevice::SetUp(int button)
{
	pImpl->SetUp(button);
}


InputDevice::ControllerImplementation::ControllerImplementation(unsigned int id)
	: InputDeviceImplementation(id)
	, m_ButtonsPressedThisFrame(0)
	, m_ButtonsReleasedThisFrame(0)
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
}

void InputDevice::ControllerImplementation::Update()
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

bool InputDevice::ControllerImplementation::IsDown(int XInputGamepadButton) const
{
	return XInputGamepadButton & m_CurrentState.Gamepad.wButtons;
}

bool InputDevice::ControllerImplementation::IsReleased(int XInputGamepadButton) const
{
	return XInputGamepadButton & m_ButtonsReleasedThisFrame;
}

bool InputDevice::ControllerImplementation::IsPressed(int XInputGamepadButton) const
{
	return XInputGamepadButton & m_ButtonsPressedThisFrame;
}

void InputDevice::ControllerImplementation::SetDown(int)
{
	// Does nothing
}

void InputDevice::ControllerImplementation::SetUp(int)
{
	// Does nothing
}

InputDevice::KeyboardImplementation::KeyboardImplementation(unsigned int id)
	: InputDeviceImplementation(id)
{
}

void InputDevice::KeyboardImplementation::Update()
{
	const std::bitset<numScanCodes> keyChanges{ m_CurrentState ^ m_PreviousState };
	m_KeysPressedThisFrame = keyChanges & m_CurrentState;
	m_KeysReleasedThisFrame = keyChanges & ~m_CurrentState;

	m_PreviousState = m_CurrentState;
}

bool InputDevice::KeyboardImplementation::IsDown(int SDL_Scancode) const
{
	return m_CurrentState[SDL_Scancode];
}

bool InputDevice::KeyboardImplementation::IsPressed(int SDL_Scancode) const
{
	return m_KeysPressedThisFrame[SDL_Scancode];
}

bool InputDevice::KeyboardImplementation::IsReleased(int SDL_Scancode) const
{
	return m_KeysReleasedThisFrame[SDL_Scancode];
}

void InputDevice::KeyboardImplementation::SetDown(int SDL_Scancode)
{
	m_CurrentState[SDL_Scancode] = true;
}

void InputDevice::KeyboardImplementation::SetUp(int SDL_Scancode)
{
	m_CurrentState[SDL_Scancode] = false;
}
