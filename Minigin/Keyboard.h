#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <memory>

#include "InputDevice.h"

namespace dae
{
	class Keyboard final: public InputDevice
	{
	public:
		explicit Keyboard(unsigned int id);
		virtual ~Keyboard() override;

		Keyboard(const Keyboard& other) = delete;
		Keyboard(Keyboard&& other) = delete;
		Keyboard& operator=(const Keyboard& other) = delete;
		Keyboard& operator=(Keyboard&& other) = delete;

		virtual void Update() override;
		[[nodiscard]] virtual bool IsDown(int SDL_Scancode) const override;
		[[nodiscard]] virtual bool IsPressed(int SDL_Scancode) const override;
		[[nodiscard]] virtual bool IsReleased(int SDL_Scancode) const override;

		void SetDown(int SDL_ScanCode) const;
		void SetUp(int SDL_ScanCode) const;

	private:
		class KeyboardImplementation;
		std::unique_ptr<KeyboardImplementation> m_pImpl;
	};
}
#endif
