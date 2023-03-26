#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "InputDevice.h"

namespace dae
{
	class Keyboard final: public InputDevice
	{
	public:
		explicit Keyboard(unsigned int id)
			: InputDevice(id, DeviceType::Keyboard) {}
		virtual ~Keyboard() override = default;
	};
}
#endif
