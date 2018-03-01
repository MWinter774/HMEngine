#pragma once
#include <vector>
#include "Word.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Font
		{
			class Line
			{
			public:
				Line(float spaceWidth, float fontSize, float maxLineLength);
				~Line();

				bool AttemptToAddWord(const HMEngine::Core::Font::Word& word);

				inline float GetMaxLineLength() const { return this->_maxLineLength; }
				inline float GetCurrentLineLength() const { return this->_currentLineLength; }
				inline std::vector<HMEngine::Core::Font::Word> GetWords() const { return this->_words; }

			private:
				float _maxLineLength;
				float _spaceSize;
				std::vector<HMEngine::Core::Font::Word> _words;
				float _currentLineLength;
			};
		}
	}
}