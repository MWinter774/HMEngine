#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace Core
	{
		class FNTFile
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
				float aa;
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
				int packed;
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
				int first;
				int second;
				int amount;
			} BMFontKerning;
		public:
			typedef struct
			{
				int id;
				int x;
				int y;
				int width;
				int height;
				int xOffset;
				int yOffset;
				int xAdvance;
				int page;
				int chnl;
			} BMFontCharacter;

			FNTFile(const std::string& fntFilePath);
			~FNTFile();

			inline std::string GetFntFilePath() const { return this->_fntFilePath; }

			HMEngine::Core::FNTFile::BMFontCharacter GetCharacter(int asciiCode);

		private:
			static std::vector<std::string>* ReadLines(std::ifstream& file);
			static std::vector<std::string> SplitString(const std::string& string, char delimiter);
			static void CheckForError(bool condition, const std::string& errorMessage);
			static bool StringToInt(int& data, const std::string& toConvert);
			static bool StringToFloat(float& data, const std::string& toConvert);
			static void StringToBool(bool& data, const std::string& toConvert);

			std::string _fntFilePath;
			BMFontInfo _info;
			BMFontCommon _common;
			BMFontPage _page;
			BMFontChars _chars;
			BMFontKernings _kernings;
			std::unordered_map<int, BMFontCharacter> _charactersMap; //maps between character code in ASCII to the character info
			std::vector<BMFontKerning> _kerningsVector; //list of all the kernings

			void ProcessLine(const std::vector<std::string>& line);
			void InitInfoHeader(const std::string& face, const std::string& size, const std::string& bold, const std::string& italic, const std::string& charset,
				const std::string& unicode, const std::string& stretchH, const std::string& smooth, const std::string& aa, const std::string& padding,
				const std::string& spacing);
			void InitCommonHeader(const std::string& lineHeight, const std::string& base, const std::string& scaleW, const std::string& scaleH,
				const std::string& pages, const std::string& packed);
			void InitPageHeader(const std::string& id, const std::string& file);
			void InitCharsHeader(const std::string& count);
			void InitKerningsHeader(const std::string& count);
			void AddCharacter(const std::string& id, const std::string& x, const std::string& y, const std::string& width, const std::string& height,
				const std::string& xOffset, const std::string& yOffset, const std::string& xAdvance, const std::string& page, const std::string& chnl);
			void AddKerning(const std::string& first, const std::string& second, const std::string& amount);
		};
	}
}