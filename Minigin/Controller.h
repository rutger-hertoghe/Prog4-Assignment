#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "InputDevice.h"

namespace dae
{
	class Controller final : public InputDevice
	{
	public:
		explicit Controller(unsigned int id)
			: InputDevice(id, DeviceType::Controller)
		{}
		// Constructor is in protected field
		virtual ~Controller() override = default;
	};
}
#endif