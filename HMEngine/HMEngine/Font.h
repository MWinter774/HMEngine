#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "glm\glm.hpp"
#include <unordered_map>
#include "FNTFile.h"

namespace HMEngine
{
	namespace UI
	{
		class Font
		{
		public:
			Font(const std::string& fntFilePath, const std::string& fntTexturePath);
			~Font();

			HMEngine::Core::FNTFile::BMFontCharacter operator[](char character) const;

			inline std::string GetFntFilePath() const { return this->_fontFile->GetFntFilePath(); }
			inline std::string GetFntTexturePath() const { return this->_fntTexturePath; }

		private:
			std::string _fntTexturePath;
			HMEngine::Core::FNTFile* _fontFile;
		};
	}
}