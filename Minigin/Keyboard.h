#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <SDL_scancode.h>
#include <bitset>

#include "InputDevice.h"

// TODO: see if both Keyboard & Controller can inherit from a possible new class InputDevice
namespace dae
{
	class Keyboard final : public InputDevice
	{
	public:
		explicit Keyboard(DWORD id);

		virtual void Update() override;

		void SetDown(SDL_Scancode key);
		void SetUp(SDL_Scancode key);

		[[nodiscard]] virtual bool IsDown(int SDL_Scancode) const override;
		[[nodiscard]] virtual bool IsPressed(int SDL_Scancode) const override;
		[[nodiscard]] virtual bool IsReleased(int SDL_Scancode) const override;

		/*[[nodiscard]] bool IsDown(SDL_Scancode key) const;
		[[nodiscard]] bool IsReleased(SDL_Scancode key) const;
		[[nodiscard]] bool IsPressed(SDL_Scancode key) const;*/

	private:
		static constexpr int numScanCodes{ static_cast<int>(SDL_NUM_SCANCODES) };
		std::bitset<numScanCodes> m_CurrentState;
		std::bitset<numScanCodes> m_PreviousState;

		std::bitset<numScanCodes> m_KeysPressedThisFrame;
		std::bitset<numScanCodes> m_KeysReleasedThisFrame;
	};
}
#endif