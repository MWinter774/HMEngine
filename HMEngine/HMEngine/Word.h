#pragma once
#include <vector>
#include "Font.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Font
		{
			class Word
			{
			public:
				Word(float fontSize);
				~Word();

				void AddCharacter(const HMEngine::Core::FNTFile::BMFontCharacter& character);

				inline std::vector<HMEngine::Core::FNTFile::BMFontCharacter> GetCharacters() const { return this->_characters; }
				inline float GetWordWidth() const { return this->_width; }

			private:
				std::vector<HMEngine::Core::FNTFile::BMFontCharacter> _characters;
				float _width;
				float _fontSize;
			};
		}
	}
}