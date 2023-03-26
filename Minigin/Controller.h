#ifndef CONTROLLER_H
#define CONTROLLER_H

//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
#include "InputDevice.h"
#include <Xinput.h>


namespace dae
{
	class Controller final : public InputDevice
	{
	public:
		explicit Controller(DWORD id);
		~Controller() override = default;

		virtual void Update() override;
		[[nodiscard]] virtual bool IsDown(int XInputGamepadButton) const override;
		[[nodiscard]] virtual bool IsReleased(int XInputGamepadButton) const override;
		[[nodiscard]] virtual bool IsPressed(int XInputGamepadButton) const override;
		
	private:
		XINPUT_STATE m_CurrentState;
		XINPUT_STATE m_PreviousState;

		int m_ButtonsPressedThisFrame;
		int m_ButtonsReleasedThisFrame;
	};
}
#endif