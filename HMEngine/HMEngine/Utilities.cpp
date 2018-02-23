#include "Utilities.h"
#include <iostream>
#include <SDL2.0.7\SDL.h>
#include <exception>
#include <windows.h>

/*
Creates an error message box with the exception message and clears up the stack.
Input:
errorMessage - the error message to display
errorTitle - the title of the error window
Output:

*/
void HMEngine::Core::Utilities::ThrowException(const std::string& errorMessage, const std::string& errorTitle)
{
	SDL_MessageBoxButtonData buttons[] = { { 0, 0, "OK" } };
	const SDL_MessageBoxData messageBoxData = {
		SDL_MESSAGEBOX_INFORMATION,
		NULL,
		errorTitle.c_str(),
		errorMessage.c_str(),
		SDL_arraysize(buttons),
		buttons,
		NULL
	};

	int buttonId = -1;
	SDL_ShowMessageBox(&messageBoxData, &buttonId);

	throw std::exception(errorMessage.c_str());
}

/*
Prints a debug message with colors.
Input:
message - the message to print
messageType - type of the messsage to print(e.g. "DEBUG" will print "[DEBUG]")
foregroundColor - foreground color of the message to print(Defualt: White)
backgroundColor - background color of the message to print(Defualt: Black)
Output:

*/
void HMEngine::Core::Utilities::PrintDebugMessage(const std::string& message, const std::string& messageType, unsigned char foregroundColor, unsigned char backgroundColor)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, foregroundColor + backgroundColor * 16);
	std::cout << "[" << messageType << "] " << message << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
}