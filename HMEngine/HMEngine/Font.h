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

			HMEngine::Core::FNTFile::Glyph operator[](char character) const;

			inline std::string GetTTFFilePath() const { return this->_fontFile->GetTTFFilePath(); }
			inline std::string GetFntTexturePath() const { return this->_fntTexturePath; }

		private:
			std::string _fntTexturePath;
			HMEngine::Core::FNTFile* _fontFile;
		};
	}
}