#include "HardwareInputs.h"

char HMEngine::Core::Hardware::HardwareInputs::_keys[HMEngine::Core::Hardware::HardwareInputs::NUM_KEYS];

/*
Updates the input from the hardware(keyboard, mouse).
*/
void HMEngine::Core::Hardware::HardwareInputs::Update()
{
	HMEngine::Core::Hardware::HardwareInputs::Reset();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			_keys[e.key.keysym.sym] |= (KeyDown | KeyTapped);
		}
		else if (e.type == SDL_KEYUP)
		{
			_keys[e.key.keysym.sym] &= ~KeyDown;
			_keys[e.key.keysym.sym] |= KeyUp;
		}
	}
}

/*
Sets all the keys to be nothing.
*/
HMEngine::Core::Hardware::HardwareInputs::HardwareInputs()
{
	memset(_keys, KeyNone, HMEngine::Core::Hardware::HardwareInputs::NUM_KEYS * sizeof(KeyState));
}

/*
Sets all the keys to be nothing, except the tapped keys.
*/
void HMEngine::Core::Hardware::HardwareInputs::Reset()
{
	for (unsigned int i = 0; i < HMEngine::Core::Hardware::HardwareInputs::NUM_KEYS; i++)
	{
		_keys[i] &= ~(KeyTapped | KeyUp);
	}
}
