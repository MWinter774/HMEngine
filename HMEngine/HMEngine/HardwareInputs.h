#pragma once
#include <SDL2.0.7\SDL.h>
#undef main
#include "glm\glm.hpp"

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
			enum MouseButtonsStates : char
			{
				MouseButtonNone = 0b000,
				MouseButtonDown = 0b001,
				MouseButtonUp = 0b010,
				MouseButtonTapped = 0b100
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
					return HardwareInputs::keys[keyCode] & KeyStates::KeyTapped;
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
					return HardwareInputs::keys[keyCode] & KeyStates::KeyDown;
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
				Returns vector representing the mouse position
				*/
				static inline glm::vec2 GetCursorPos()
				{
					return glm::vec2(HardwareInputs::cursorXPos, HardwareInputs::cursorYPos);
				}

				/*
				Sets the cursor position.
				*/
				static inline void SetCursorPos(int xPos, int yPos)
				{
					SDL_WarpMouseInWindow(HardwareInputs::window, xPos, yPos); //NEEDS A WINDOW!!!!!!!!!!
				}

				/*
				Returns if the mouse button is tapped.
				Input:
				mouseButtonCode - the code of the mouse button(for example SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT...)
				Output:
				Returns whether the mouse button is tapped or not.
				*/
				static inline bool IsMouseButtonTapped(unsigned int mouseButtonCode)
				{
					return HardwareInputs::mouseButtons[mouseButtonCode] & MouseButtonsStates::MouseButtonTapped;
				}

				/*
				Returns if the mouse button is held down.
				Input:
				mouseButtonCode - the code of the key(for example SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT...)
				Output:
				Returns whether the mouse button is held down or not.
				*/
				static inline bool IsMouseButtonDown(unsigned int mouseButtonCode)
				{
					return HardwareInputs::mouseButtons[mouseButtonCode] & MouseButtonsStates::MouseButtonDown;
				}

				/*
				Sets the target window to record the inputs from.
				*/
				static inline void SetWindow(SDL_Window* window)
				{
					HardwareInputs::window = window;
				}

			private:
				typedef char KeyState;
				typedef char MouseButtonState;
				static const unsigned int NUM_KEYS = 236U;
				static const unsigned int NUM_MOUSE_BUTTONS = 5U;

				static void Reset();

				static KeyState keys[NUM_KEYS];
				static MouseButtonState mouseButtons[NUM_MOUSE_BUTTONS];
				static SDL_Event e;
				static int cursorXPos;
				static int cursorYPos;
				static SDL_Window* window;
			};
		}
	}
}