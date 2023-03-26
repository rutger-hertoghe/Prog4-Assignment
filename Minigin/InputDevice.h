#ifndef INPUT_DEVICE_H
#define	INPUT_DEVICE_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace dae
{
	class InputDevice
	{
	public:
		// Constructor is in protected field
		virtual ~InputDevice() = default;

		virtual void Update() = 0;

		[[nodiscard]] virtual bool IsDown(int XInputGamepadButton) const = 0;
		[[nodiscard]] virtual bool IsReleased(int XInputGamepadButton) const = 0;
		[[nodiscard]] virtual bool IsPressed(int XInputGamepadButton) const = 0;

	protected:
		InputDevice(DWORD id)
			: m_DeviceID{ id }
		{}

		DWORD m_DeviceID;
	};
}
#endif