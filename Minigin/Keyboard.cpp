#include "Keyboard.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

dae::Keyboard::Keyboard(DWORD id)
	: InputDevice(id)
{
}

// Place after key processing by SDL
void dae::Keyboard::Update()
{
	const std::bitset<numScanCodes> keyChanges{ m_CurrentState ^ m_PreviousState };
	m_KeysPressedThisFrame = keyChanges & m_CurrentState;
	m_KeysReleasedThisFrame = keyChanges & ~m_CurrentState;

	m_PreviousState = m_CurrentState;
}

void dae::Keyboard::SetDown(SDL_Scancode key)
{
	m_CurrentState[key] = true;
}

void dae::Keyboard::SetUp(SDL_Scancode key)
{
	m_CurrentState[key] = false;
}

bool dae::Keyboard::IsDown(int SDL_Scancode) const
{
	return m_CurrentState[SDL_Scancode];
}

bool dae::Keyboard::IsPressed(int SDL_Scancode) const
{
	return m_KeysPressedThisFrame[SDL_Scancode];
}

bool dae::Keyboard::IsReleased(int SDL_Scancode) const
{
	return m_KeysReleasedThisFrame[SDL_Scancode];
}
