#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace UI
	{
		class Font
		{
			typedef struct
			{
				std::string face;
				int size;
				bool bold;
				bool italic;
				std::string charset;
				bool unicode;
				int stretchH;
				bool smooth;
				int aa;
				glm::vec4 padding;
				glm::vec2 spacing;
			} BMFontInfo;

			typedef struct
			{
				int lineHeight;
				int base;
				int scaleW;
				int scaleH;
				int pages;
				bool packed;
			} BMFontCommon;

			typedef struct
			{
				int id;
				std::string file;
			} BMFontPage;

			typedef struct
			{
				int count;
			} BMFontChars;

			typedef struct
			{
				int count;
			} BMFontKernings;

			typedef struct
			{
				BMFontInfo info;
				BMFontCommon common;
				BMFontPage page;
				BMFontChars chars;
				BMFontKernings kernings;
			} BMFontHeader;

		public:
			Font(const std::string& fntFilePath);
			~Font();
			Font(const HMEngine::UI::Font& other);
			HMEngine::UI::Font& operator=(const HMEngine::UI::Font& other);

		private:
			static std::vector<std::string>* ReadLines(std::ifstream& file);
			static std::vector<std::string>* SplitString(const std::string& string, char delimiter);
			static std::string GetFirstWord(const std::string& string, char delimiter);

			std::string _fntFilePath;
			std::ifstream _fntFile;
			BMFontHeader _header;

			void ProcessLine(const std::vector<std::string>& line);
		};
	}
}