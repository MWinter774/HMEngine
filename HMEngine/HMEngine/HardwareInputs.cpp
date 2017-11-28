#include "HardwareInputs.h"

int HMEngine::Core::Hardware::HardwareInputs::_keys[HMEngine::Core::Hardware::HardwareInputs::NUM_KEYS];

/*
Updates the input from the hardware(keyboard, mouse).
*/
void HMEngine::Core::Hardware::HardwareInputs::Update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			_keys[e.key.keysym.scancode] = KeyDown | KeyTapped;
			_keys[(int)HMEngine::Keys::KEY_W] = 0x100;
		}
		else if (e.type == SDL_KEYUP)
		{
			_keys[e.key.keysym.scancode] &= ~KeyTapped;
			_keys[e.key.keysym.scancode] |= KeyUp;
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

HMEngine::Core::Hardware::HardwareInputs::~HardwareInputs()
{
}

/*
Sets all the keys to be nothing, except the tapped keys.
*/
void HMEngine::Core::Hardware::HardwareInputs::Reset()
{
	for (unsigned int i = 0; i < HMEngine::Core::Hardware::HardwareInputs::NUM_KEYS; i++)
	{
		_keys[i] &= ~(KeyDown | KeyUp);
	}
}
