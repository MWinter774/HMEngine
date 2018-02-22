#pragma once
#include <string>
#include <vector>
#include "glm\glm.hpp"
#include "Font.h"

namespace HMEngine
{
	namespace UI
	{
		class Font;
	}

	namespace Core
	{
		class Utilities
		{
		public:
			static void ThrowException(const std::string& errorMessage, const std::string& errorTitle = "Error!");
			static void PrintDebugMessage(const std::string& message, const std::string& messageType = "DEBUG", unsigned char foregroundColor = 7, unsigned char backgroundColor = 0);

			static std::pair<std::vector<glm::vec2>, std::vector<glm::vec2>> GetVerticesAndUVsFromText(const std::string& text, const HMEngine::UI::Font& font);
		private:
			Utilities() = delete;
			~Utilities() = delete;

			//static void AddVerticesForCharacter(std::vector<glm::vec2>& vertices, const HMEngine::Core::FNTFile::BMFontCharacter& character, float cursorX, float cursorY, float fontSize);
			static void AddVertices(std::vector<glm::vec2>& vertices, float x, float y, float maxX, float maxY);
			static void AddUVs(std::vector<glm::vec2>& uvs, float x, float y, float maxX, float maxY);
		};
	}
}