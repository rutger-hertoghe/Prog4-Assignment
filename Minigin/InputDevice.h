#ifndef INPUT_DEVICE_H
#define	INPUT_DEVICE_H
namespace dae
{
	class InputDevice
	{
	public:
		// Constructor is in protected field
		virtual ~InputDevice() = default;

		InputDevice(const InputDevice& other) = delete;
		InputDevice(InputDevice&& other) = delete;
		InputDevice& operator=(const InputDevice& other) = delete;
		InputDevice& operator=(InputDevice&& other) = delete;

		virtual void Update() = 0;

		[[nodiscard]] virtual bool IsDown(int button) const = 0;
		[[nodiscard]] virtual bool IsReleased(int button) const = 0;
		[[nodiscard]] virtual bool IsPressed(int button) const = 0;

	protected:
		explicit InputDevice() = default;
	/*	explicit InputDevice(unsigned int id)
			: m_DeviceID{ id }
		{}

		unsigned int GetDeviceID() const
		{
			return m_DeviceID;
		}

	private:
		unsigned int m_DeviceID;*/
	};
}
#endif