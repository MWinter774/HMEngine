#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Hardware
		{
			enum KeyStates : char
			{
				KeyNone = 0b000,
				KeyDown = 0b001,
				KeyUp = 0b010,
				KeyTapped = 0b100
			};
			class HardwareInputs
			{
			public:

				static void Update();

				/*
				Returns if the key is tapped.
				Input:
				keyCode - the code of the key(for example SDLK_w, SDLK_g, SDLK_4...)
				Output:
				Returns whether the key is tapped or not.
				*/
				static inline bool IsKeyTapped(unsigned int keyCode)
				{
					return _keys[keyCode] & KeyTapped;
				}

				/*
				Returns if the key is held down.
				Input:
				keyCode - the code of the key(for example SDLK_w, SDLK_g, SDLK_4...)
				Output:
				Returns whether the key is held down or not.
				*/
				static inline bool IsKeyDown(unsigned int keyCode)
				{
					return _keys[keyCode] & KeyDown;
				}

			private:
				HardwareInputs();
				~HardwareInputs() = delete;

				typedef char KeyState;
				static const unsigned int NUM_KEYS = 236U;

				static void Reset();

				static KeyState _keys[NUM_KEYS];
			};
		}
	}
}