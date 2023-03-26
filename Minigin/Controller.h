#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <windows.h>
#include <Xinput.h>

namespace dae
{
	class Controller final
	{
	public:
		Controller(DWORD id);
		~Controller() = default;

		void Update();
		[[nodiscard]] bool IsDown(int XInputGamepadButton) const;
		[[nodiscard]] bool IsReleased(int XInputGamepadButton) const;
		[[nodiscard]] bool IsPressed(int XInputGamepadButton) const;
		
	private:
		DWORD m_ControllerID;

		XINPUT_STATE m_CurrentState;
		XINPUT_STATE m_PreviousState;

		int m_ButtonsPressedThisFrame;
		int m_ButtonsReleasedThisFrame;
	};
}
#endif