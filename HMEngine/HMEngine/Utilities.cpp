#include "Utilities.h"
#include <SDL2.0.7\SDL.h>
#include <exception>

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