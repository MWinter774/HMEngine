#include "Line.h"

HMEngine::Core::Font::Line::Line(float spaceWidth, float fontSize, float maxLineLength) : _maxLineLength(maxLineLength), _spaceSize(spaceWidth * fontSize), _words(),
_currentLineLength(0)
{
}

HMEngine::Core::Font::Line::~Line()
{
}

bool HMEngine::Core::Font::Line::AttemptToAddWord(const HMEngine::Core::Font::Word& word)
{
	float additionalLength = word.GetWordWidth();
	additionalLength += this->_words.size() > 0 ? this->_spaceSize : 0;
	if (this->_currentLineLength + additionalLength <= this->_maxLineLength)
	{
		this->_words.push_back(word);
		this->_currentLineLength += additionalLength;
		return true;
	}
	return false;
}
