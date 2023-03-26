#ifndef INPUT_DEVICE_H
#define	INPUT_DEVICE_H
#include <memory>
namespace dae
{
	enum class DeviceType
	{
		Controller,
		Keyboard
	};

	enum class GamePad
	{
		A				= 0x1000,
		B				= 0x2000,
		X				= 0x4000,
		Y				= 0x8000,
		LeftShoulder	= 0x0100,
		RightShoulder	= 0x0200,
		Start			= 0x0010,
		Back			= 0x0020,
		DPadUp			= 0x0001,
		DPadDown		= 0x0002,
		DPadRight		= 0x0008,
		DPadLeft		= 0x0004
	};

	class InputDevice
	{
	public:
		explicit InputDevice(unsigned int id, DeviceType deviceType);
		// Constructor is in protected field
		virtual ~InputDevice();

		virtual void Update();

		[[nodiscard]] virtual bool IsDown(int button) const;
		[[nodiscard]] virtual bool IsReleased(int button) const;
		[[nodiscard]] virtual bool IsPressed(int button) const;

		virtual void SetDown(int button);
		virtual void SetUp(int button);

	protected:
		class InputDeviceImplementation;
		class KeyboardImplementation;
		class ControllerImplementation;

		std::unique_ptr<InputDeviceImplementation> pImpl;
	};
}
#endif