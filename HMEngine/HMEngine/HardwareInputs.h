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
				HardwareInputs() = delete;
				~HardwareInputs() = delete;

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
					return keys[keyCode] & KeyTapped;
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
					return keys[keyCode] & KeyDown;
				}

				/*
				Sets the cursor x position.
				*/
				static inline void SetCursorXPos(int xPos)
				{
					HardwareInputs::cursorXPos = xPos;
				}

				/*
				Sets the cursor y position.
				*/
				static inline void SetCursorYPos(int yPos)
				{
					HardwareInputs::cursorYPos = yPos;
				}

				/*
				Returns the x position of the cursor.
				*/
				static inline int GetCursorXPos()
				{
					return HardwareInputs::cursorXPos;
				}


				/*
				Returns the y position of the cursor.
				*/
				static inline int GetCursorYPos()
				{
					return HardwareInputs::cursorYPos;
				}

				/*
				Sets the cursor position.
				*/
				static inline void SetCursorPos(int xPos, int yPos)
				{
					SDL_WarpMouseInWindow(nullptr, xPos, yPos); //NEEDS A WINDOW!!!!!!!!!!
				}

			private:
				typedef char KeyState;
				static const unsigned int NUM_KEYS = 236U;

				static void Reset();

				static KeyState keys[NUM_KEYS];
				static SDL_Event e;
				static int cursorXPos;
				static int cursorYPos;
			};
		}
	}
}