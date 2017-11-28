#pragma once
#include "HMEngineIncludes.h"
#include "Keys.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Hardware
		{
			class HardwareInputs
			{
			public:
				static void Update();

			private:
				enum KeyStates : char
				{
					KeyNone = 0x000,
					KeyDown = 0x001,
					KeyUp = 0x002,
					KeyTapped = 0x004
				};
				typedef int KeyState;
				static const unsigned int NUM_KEYS = (unsigned int)HMEngine::Keys::NUM_KEYS;

				HardwareInputs();
				~HardwareInputs();

				static void Reset();

				static KeyState _keys[NUM_KEYS];
			};
		}
	}
}