#include "HardwareInputs.h"

char HMEngine::Core::Hardware::HardwareInputs::keys[HMEngine::Core::Hardware::HardwareInputs::NUM_KEYS] = { KeyStates::KeyNone };
char HMEngine::Core::Hardware::HardwareInputs::mouseButtons[HMEngine::Core::Hardware::HardwareInputs::NUM_MOUSE_BUTTONS] = { MouseButtonsStates::MouseButtonNone };
SDL_Event HMEngine::Core::Hardware::HardwareInputs::e;
int HMEngine::Core::Hardware::HardwareInputs::cursorXPos = 0;
int HMEngine::Core::Hardware::HardwareInputs::cursorYPos = 0;

/*
Updates the input from the hardware(keyboard, mouse).
*/
void HMEngine::Core::Hardware::HardwareInputs::Update()
{
	HardwareInputs::Reset();

	while (SDL_PollEvent(&HardwareInputs::e))
	{
		if (e.type == SDL_MOUSEMOTION)
		{
			HardwareInputs::cursorXPos = e.motion.x;
			HardwareInputs::cursorYPos = e.motion.y;
		}
		else if (HardwareInputs::e.type == SDL_KEYDOWN)
		{
			HardwareInputs::keys[HardwareInputs::e.key.keysym.sym] |= (KeyStates::KeyDown | KeyStates::KeyTapped); //turn on the KeyDown and KeyTapped bits
		}
		else if (HardwareInputs::e.type == SDL_KEYUP)
		{
			HardwareInputs::keys[HardwareInputs::e.key.keysym.sym] &= ~KeyStates::KeyDown; //turn off the KeyDown bit
			HardwareInputs::keys[HardwareInputs::e.key.keysym.sym] |= KeyStates::KeyUp; //turn on the KeyUp bit
		}
		else if (HardwareInputs::e.type == SDL_MOUSEBUTTONDOWN)
		{
			HardwareInputs::mouseButtons[HardwareInputs::e.button.button] |= (MouseButtonsStates::MouseButtonDown | MouseButtonsStates::MouseButtonTapped); //turn on the KeyDown and KeyTapped bits
		}
		else if (HardwareInputs::e.type == SDL_MOUSEBUTTONUP)
		{
			HardwareInputs::mouseButtons[HardwareInputs::e.button.button] &= ~MouseButtonsStates::MouseButtonDown; //turn off the KeyDown bit
			HardwareInputs::mouseButtons[HardwareInputs::e.button.button] |= MouseButtonsStates::MouseButtonUp; //turn on the KeyUp bit
		}
	}
}

/*
Sets all the keys to be nothing, except the held down keys.
*/
void HMEngine::Core::Hardware::HardwareInputs::Reset()
{
	for (unsigned int i = 0; i < HMEngine::Core::Hardware::HardwareInputs::NUM_KEYS; i++)
	{
		HardwareInputs::keys[i] &= ~(KeyStates::KeyTapped | KeyStates::KeyUp); //turn off the the KeyUp and KeyTapped bits
	}

	for (unsigned int i = 0; i < HMEngine::Core::Hardware::HardwareInputs::NUM_MOUSE_BUTTONS; i++)
	{
		HardwareInputs::mouseButtons[i] &= ~(MouseButtonsStates::MouseButtonTapped | MouseButtonsStates::MouseButtonUp); //turn off the the KeyUp and KeyTapped bits
	}
}
