#include "Font.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "FNTFileManager.h"

HMEngine::UI::Font::Font(const std::string& ttfFilePath, const std::string& fntTexturePath) : _fntTexturePath(fntTexturePath)
{
	this->_fontFile = &HMEngine::UI::FNTFileManager::GetFont(ttfFilePath);
}

HMEngine::UI::Font::~Font()
{
}

HMEngine::Core::FNTFile::Glyph HMEngine::UI::Font::operator[](char character) const
{
	return this->_fontFile->GetCharacter(character);
}