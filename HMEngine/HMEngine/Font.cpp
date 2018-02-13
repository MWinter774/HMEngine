#include "Font.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>

HMEngine::UI::Font::Font(const std::string& fntFilePath) : _fntFile(fntFilePath), _fntFilePath(fntFilePath)
{
	std::vector<std::string>* lines = HMEngine::UI::Font::ReadLines(this->_fntFile);
	std::vector<std::string>* words = nullptr;
	for (auto& line : *lines)
	{
		words = HMEngine::UI::Font::SplitString(line, ' ');

		this->ProcessLine(*words);

		delete words;
	}

	delete lines;
}

HMEngine::UI::Font::~Font()
{
	this->_fntFile.close();
}

HMEngine::UI::Font::Font(const HMEngine::UI::Font& other) : _fntFile(other._fntFilePath), _fntFilePath(other._fntFilePath), _header(other._header)
{
}

HMEngine::UI::Font& HMEngine::UI::Font::operator=(const HMEngine::UI::Font& other)
{
	if (this != &other)
	{
		this->_fntFilePath = other._fntFilePath;
		this->_fntFile.close();
		this->_fntFile = std::ifstream(this->_fntFilePath);
		this->_header = other._header;
	}

	return *this;
}

std::vector<std::string>* HMEngine::UI::Font::ReadLines(std::ifstream& file)
{
	std::vector<std::string>* lines = new std::vector<std::string>();
	std::string currLine;

	while (std::getline(file, currLine))
	{
		lines->push_back(currLine);
	}

	return lines;
}

std::vector<std::string>* HMEngine::UI::Font::SplitString(const std::string& string, char delimiter)
{
	std::vector<std::string>* strings = new std::vector<std::string>();
	std::string currWord;
	std::istringstream stringStream(string);

	while (std::getline(stringStream, currWord, delimiter))
	{
		if (!currWord.empty())
			strings->push_back(currWord);
	}

	return strings;
}

std::string HMEngine::UI::Font::GetFirstWord(const std::string& line, char delimiter)
{
	std::vector<std::string>* strings = new std::vector<std::string>();
	std::string word;
	std::istringstream stringStream(line);

	std::getline(stringStream, word, delimiter);

	return word;
}

void HMEngine::UI::Font::ProcessLine(const std::vector<std::string>& line)
{
	if (line.size() < 2)
		HMEngine::Core::Utilities::ThrowException("INVALID .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);
	if (line[0] == "info")
	{

	}
	else if (line[0] == "common")
	{
		std::cout << "this is a common line" << std::endl;
	}
	else if (line[0] == "page")
	{
		std::cout << "this is a page line" << std::endl;
	}
	else if (line[0] == "chars")
	{
		std::cout << "this is a chars line" << std::endl;
	}
	else if (line[0] == "char")
	{
		std::cout << "this is a char line" << std::endl;
	}
	else if (line[0] == "kernings")
	{
		std::cout << "this is a kernings line" << std::endl;
	}
	else if (line[0] == "kerning")
	{
		std::cout << "this is a kerning line" << std::endl;
	}
}