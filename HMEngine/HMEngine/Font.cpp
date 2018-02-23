#include "Font.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "FNTFileManager.h"

HMEngine::UI::Font::Font(const std::string& fntFilePath, const std::string& fntTexturePath) : _fntTexturePath(fntTexturePath)
{
	this->_fontFile = &HMEngine::UI::FNTFileManager::GetFont(fntFilePath);
}

HMEngine::UI::Font::~Font()
{
}

HMEngine::Core::FNTFile::BMFontCharacter HMEngine::UI::Font::operator[](char character) const
{
	return this->_fontFile->GetCharacter(character);
}