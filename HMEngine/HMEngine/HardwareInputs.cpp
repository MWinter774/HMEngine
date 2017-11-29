#include "HardwareInputs.h"

char HMEngine::Core::Hardware::HardwareInputs::keys[HMEngine::Core::Hardware::HardwareInputs::NUM_KEYS] = { KeyStates::KeyNone };
SDL_Event HMEngine::Core::Hardware::HardwareInputs::e;
int HMEngine::Core::Hardware::HardwareInputs::cursorXPos = 0;
int HMEngine::Core::Hardware::HardwareInputs::cursorYPos = 0;

/*
Updates the input from the hardware(keyboard, mouse).
*/
void HMEngine::Core::Hardware::HardwareInputs::Update()
{
	HMEngine::Core::Hardware::HardwareInputs::Reset();

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
}
