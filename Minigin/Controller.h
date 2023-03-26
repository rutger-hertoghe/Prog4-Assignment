#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include "InputDevice.h"

namespace dae
{
	enum class GamePad
	{
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		Start = 0x0010,
		Back = 0x0020,
		DPadUp = 0x0001,
		DPadDown = 0x0002,
		DPadRight = 0x0008,
		DPadLeft = 0x0004
	};

	class Controller final : public InputDevice
	{
	public:
		explicit Controller(unsigned int id);
		virtual ~Controller() override;

		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		virtual void Update() override;
		[[nodiscard]] virtual bool IsDown(int XInputGamepadButton) const override;
		[[nodiscard]] virtual bool IsPressed(int XInputGamepadButton) const override;
		[[nodiscard]] virtual bool IsReleased(int XInputGamepadButton) const override;

	private:
		class ControllerImplementation;
		std::unique_ptr<ControllerImplementation> m_pImpl;
	};
}
#endif