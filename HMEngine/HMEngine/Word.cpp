#include "Word.h"

HMEngine::Core::Font::Word::Word(float fontSize) : _characters(), _width(0), _fontSize(fontSize)
{
}

HMEngine::Core::Font::Word::~Word()
{
}

void HMEngine::Core::Font::Word::AddCharacter(const HMEngine::Core::FNTFile::BMFontCharacter& character)
{
	this->_characters.push_back(character);
	this->_width += character.xAdvance * this->_fontSize;
}