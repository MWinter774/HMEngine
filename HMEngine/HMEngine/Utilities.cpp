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

std::pair<std::vector<glm::vec2>, std::vector<glm::vec2>> HMEngine::Core::Utilities::GetVerticesAndUVsFromText(const std::string& text, 
	const HMEngine::UI::Font& font)
{
	float cursorX = 0;
	float cursorY = 0;

	std::vector<glm::vec2> vertices = std::vector<glm::vec2>();
	std::vector<glm::vec2> uvs = std::vector<glm::vec2>();

	for (auto& character : text)
	{
		//HMEngine::Core::FNTFile::BMFontCharacter fntChar = font[character];
		//HMEngine::Core::Utilities::AddVerticesForCharacter(vertices, fntChar, cursorX, cursorY, 3);
		//HMEngine::Core::Utilities::AddUVs(uvs, fntChar.xTextureCoordiante, fntChar.yTextureCoordiante, fntChar.xMaxTextureCoordinate, fntChar.yMaxTextureCoordinate);

		//cursorX += fntChar.xAdvance * 3;
	}

	return std::pair<std::vector<glm::vec2>, std::vector<glm::vec2>>(vertices, uvs);
}

//void HMEngine::Core::Utilities::AddVerticesForCharacter(std::vector<glm::vec2>& vertices, const HMEngine::Core::FNTFile::BMFontCharacter& character, 
//	float cursorX, float cursorY, float fontSize)
//{
//	float x = cursorX + (character.xOffset * fontSize);
//	float y = cursorY + (character.yOffset * fontSize);
//	float maxX = x + (character.quadWidth * fontSize);
//	float maxY = y + (character.quadHeight * fontSize);
//	float properX = (2 * x) - 1;
//	float properY = (-2 * y) + 1;
//	float properMaxX = (2 * maxX) - 1;
//	float properMaxY = (-2 * maxY) + 1;
//	HMEngine::Core::Utilities::AddVertices(vertices, properX, properY, properMaxX, properMaxY);
//	//HMEngine::Core::Utilities::AddVertices(vertices, x, y, maxX, maxY);
//}

void HMEngine::Core::Utilities::AddVertices(std::vector<glm::vec2>& vertices, float x, float y, float maxX, float maxY)
{
	vertices.push_back(glm::vec2(x, y));
	vertices.push_back(glm::vec2(x, maxY));
	vertices.push_back(glm::vec2(maxX, maxY));
	vertices.push_back(glm::vec2(maxX, maxY));
	vertices.push_back(glm::vec2(maxX, y));
	vertices.push_back(glm::vec2(x, y));
}

void HMEngine::Core::Utilities::AddUVs(std::vector<glm::vec2>& uvs, float x, float y, float maxX, float maxY)
{
	uvs.push_back(glm::vec2( x, 1 - y));
	uvs.push_back(glm::vec2( x, 1 - maxY));
	uvs.push_back(glm::vec2( maxX, 1 - maxY));
	uvs.push_back(glm::vec2( maxX, 1 - maxY));
	uvs.push_back(glm::vec2(maxX, 1 - y));
	uvs.push_back(glm::vec2( x, 1 - y));
}
