#include "Keyboard.h"

#include <bitset>
#include <SDL_scancode.h>

using namespace dae;

class Keyboard::KeyboardImplementation final
{
public:
	KeyboardImplementation() = default;

	void Update();
	[[nodiscard]] bool IsDown(int SDL_ScanCode) const;
	[[nodiscard]] bool IsPressed(int SDL_ScanCode) const;
	[[nodiscard]] bool IsReleased(int SDL_ScanCode) const;

	void SetDown(int SDL_ScanCode);
	void SetUp(int SDL_ScanCode);

private:
	static constexpr int numScanCodes{ static_cast<int>(SDL_NUM_SCANCODES) };
	std::bitset<numScanCodes> m_CurrentState;
	std::bitset<numScanCodes> m_PreviousState;

	std::bitset<numScanCodes> m_KeysPressedThisFrame;
	std::bitset<numScanCodes> m_KeysReleasedThisFrame;
};

dae::Keyboard::Keyboard(/*unsigned int id*/)
	//: InputDevice(id)
{
	m_pImpl = std::make_unique<KeyboardImplementation>();
}

// Located here, because smart_ptr otherwise determines Implementation to be incomplete
dae::Keyboard::~Keyboard() = default;

void dae::Keyboard::Update()
{
	return m_pImpl->Update();
}

bool dae::Keyboard::IsDown(int SDL_ScanCode) const
{
	return m_pImpl->IsDown(SDL_ScanCode);
}

bool dae::Keyboard::IsPressed(int SDL_ScanCode) const
{
	return m_pImpl->IsPressed(SDL_ScanCode);
}

bool dae::Keyboard::IsReleased(int SDL_ScanCode) const
{
	return m_pImpl->IsReleased(SDL_ScanCode);
}

void dae::Keyboard::SetDown(int SDL_ScanCode) const
{
	m_pImpl->SetDown(SDL_ScanCode);
}

void dae::Keyboard::SetUp(int SDL_ScanCode) const
{
	m_pImpl->SetUp(SDL_ScanCode);
}

void Keyboard::KeyboardImplementation::Update()
{
	const std::bitset<numScanCodes> keyChanges{ m_CurrentState ^ m_PreviousState };
	m_KeysPressedThisFrame = keyChanges & m_CurrentState;
	m_KeysReleasedThisFrame = keyChanges & ~m_CurrentState;

	m_PreviousState = m_CurrentState;
}

bool Keyboard::KeyboardImplementation::IsDown(int SDL_ScanCode) const
{
	return m_CurrentState[SDL_ScanCode];
}

bool Keyboard::KeyboardImplementation::IsPressed(int SDL_ScanCode) const
{
	return m_KeysPressedThisFrame[SDL_ScanCode];
}

bool Keyboard::KeyboardImplementation::IsReleased(int SDL_ScanCode) const
{
	return m_KeysReleasedThisFrame[SDL_ScanCode];
}

void Keyboard::KeyboardImplementation::SetDown(int SDL_ScanCode)
{
	m_CurrentState[SDL_ScanCode] = true;
}

void Keyboard::KeyboardImplementation::SetUp(int SDL_ScanCode)
{
	m_CurrentState[SDL_ScanCode] = false;
}
