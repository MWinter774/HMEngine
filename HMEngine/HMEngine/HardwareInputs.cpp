#include "HardwareInputs.h"

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
			this->_keys[e.key.keysym.scancode] = KeyDown | KeyTapped;
		}
		else if (e.type == SDL_KEYUP)
		{
			this->_keys[e.key.keysym.scancode] &= ~KeyTapped;
			this->_keys[e.key.keysym.scancode] |= KeyUp;
		}
	}
}

/*
Sets all the keys to be nothing.
*/
HMEngine::Core::Hardware::HardwareInputs::HardwareInputs()
{
	memset(this->_keys, KeyNone, HMEngine::Core::Hardware::HardwareInputs::NUM_KEYS * sizeof(KeyState));
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
		this->_keys[i] &= ~(KeyDown | KeyUp);
	}
}
