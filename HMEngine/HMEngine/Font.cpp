#include "Font.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <algorithm>

HMEngine::UI::Font& HMEngine::UI::Font::ARIAL = HMEngine::UI::Font("./resources/fonts/arial.fnt");

HMEngine::UI::Font::Font(const std::string& fntFilePath) : _fntFile(fntFilePath), _fntFilePath(fntFilePath)
{
	std::vector<std::string>* lines = HMEngine::UI::Font::ReadLines(this->_fntFile);
	std::vector<std::string> words;
	for (auto& line : *lines)
	{
		words = HMEngine::UI::Font::SplitString(line, ' ');

		this->ProcessLine(words);
	}

	delete lines;
}

HMEngine::UI::Font::~Font()
{
	this->_fntFile.close();
}

HMEngine::UI::Font::Font(const HMEngine::UI::Font& other) : _fntFile(other._fntFilePath), _fntFilePath(other._fntFilePath), _fontFile(other._fontFile)
{
}

HMEngine::UI::Font& HMEngine::UI::Font::operator=(const HMEngine::UI::Font& other)
{
	if (this != &other)
	{
		this->_fntFilePath = other._fntFilePath;
		this->_fntFile.close();
		this->_fntFile = std::ifstream(this->_fntFilePath);
		this->_fontFile = other._fontFile;
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

std::vector<std::string> HMEngine::UI::Font::SplitString(const std::string& string, char delimiter)
{
	std::vector<std::string> strings = std::vector<std::string>();
	std::string currWord;
	std::istringstream stringStream(string);

	while (std::getline(stringStream, currWord, delimiter))
	{
		if (!currWord.empty())
			strings.push_back(currWord);
	}

	return strings;
}

void HMEngine::UI::Font::CheckForError(bool condition, const std::string & errorMessage)
{
	if (condition)
		HMEngine::Core::Utilities::ThrowException(errorMessage);
}

bool HMEngine::UI::Font::StringToInt(int& data, const std::string& toConvert)
{
	try
	{
		data = std::stoi(toConvert);
	}
	catch (...)
	{
		data = -1;
		return false;
	}
	return true;
}

bool HMEngine::UI::Font::StringToFloat(float& data, const std::string& toConvert)
{
	try
	{
		data = std::stof(toConvert);
	}
	catch (...)
	{
		data = -1;
		return false;
	}
	return true;
}

void HMEngine::UI::Font::StringToBool(bool& data, const std::string& toConvert)
{
	data = toConvert[0] == '1';
}

void HMEngine::UI::Font::ProcessLine(const std::vector<std::string>& words)
{
	HMEngine::UI::Font::CheckForError(words.size() == 0, "INVALID .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);

	if (words[0] == "char")
	{
		HMEngine::UI::Font::CheckForError(words.size() != 11, "INVALID char TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);

		/* Gets all parameters from the char tag in .fnt file format and check their propriety */
		std::vector<std::string> id = HMEngine::UI::Font::SplitString(words[1], '=');
		HMEngine::UI::Font::CheckForError(id.size() != 2, "INVALID id PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> x = HMEngine::UI::Font::SplitString(words[2], '=');
		HMEngine::UI::Font::CheckForError(x.size() != 2, "INVALID x PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> y = HMEngine::UI::Font::SplitString(words[3], '=');
		HMEngine::UI::Font::CheckForError(y.size() != 2, "INVALID y PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> width = HMEngine::UI::Font::SplitString(words[4], '=');
		HMEngine::UI::Font::CheckForError(width.size() != 2, "INVALID width PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> height = HMEngine::UI::Font::SplitString(words[5], '=');
		HMEngine::UI::Font::CheckForError(height.size() != 2, "INVALID height PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> xOffset = HMEngine::UI::Font::SplitString(words[6], '=');
		HMEngine::UI::Font::CheckForError(xOffset.size() != 2, "INVALID xOffset PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> yOffset = HMEngine::UI::Font::SplitString(words[7], '=');
		HMEngine::UI::Font::CheckForError(yOffset.size() != 2, "INVALID yOffset PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> xAdvance = HMEngine::UI::Font::SplitString(words[8], '=');
		HMEngine::UI::Font::CheckForError(xAdvance.size() != 2, "INVALID xAdvance PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> page = HMEngine::UI::Font::SplitString(words[9], '=');
		HMEngine::UI::Font::CheckForError(page.size() != 2, "INVALID page PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> chnl = HMEngine::UI::Font::SplitString(words[10], '=');
		HMEngine::UI::Font::CheckForError(chnl.size() != 2, "INVALID chnl PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

		this->AddCharacter(id[1], x[1], y[1], width[1], height[1], xOffset[1], yOffset[1], xAdvance[1], page[1], chnl[1]);
	}
	else if (words[0] == "kerning")
	{
		HMEngine::UI::Font::CheckForError(words.size() != 4, "INVALID kerning TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);

		/* Gets all parameters from the kerning tag in .fnt file format and check their propriety */
		std::vector<std::string> first = HMEngine::UI::Font::SplitString(words[1], '=');
		HMEngine::UI::Font::CheckForError(first.size() != 2, "INVALID first PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> second = HMEngine::UI::Font::SplitString(words[2], '=');
		HMEngine::UI::Font::CheckForError(second.size() != 2, "INVALID second PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> amount = HMEngine::UI::Font::SplitString(words[3], '=');
		HMEngine::UI::Font::CheckForError(amount.size() != 2, "INVALID amount PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

		this->AddKerning(first[1], second[1], amount[1]);
	}
	else if (words[0] == "info")
	{
		HMEngine::UI::Font::CheckForError(words.size() != 12, "INVALID info TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);

		/* Gets all parameters from the info tag in .fnt file format and check their propriety */
		std::vector<std::string> face = HMEngine::UI::Font::SplitString(words[1], '=');
		HMEngine::UI::Font::CheckForError(face.size() != 2, "INVALID face PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> size = HMEngine::UI::Font::SplitString(words[2], '=');
		HMEngine::UI::Font::CheckForError(size.size() != 2, "INVALID size PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> bold = HMEngine::UI::Font::SplitString(words[3], '=');
		HMEngine::UI::Font::CheckForError(bold.size() != 2, "INVALID bold PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> italic = HMEngine::UI::Font::SplitString(words[4], '=');
		HMEngine::UI::Font::CheckForError(italic.size() != 2, "INVALID italic PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> charset = HMEngine::UI::Font::SplitString(words[5], '=');
		HMEngine::UI::Font::CheckForError(charset.size() != 2, "INVALID charset PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> unicode = HMEngine::UI::Font::SplitString(words[6], '=');
		HMEngine::UI::Font::CheckForError(unicode.size() != 2, "INVALID unicode PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> stretchH = HMEngine::UI::Font::SplitString(words[7], '=');
		HMEngine::UI::Font::CheckForError(stretchH.size() != 2, "INVALID stretchH PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> smooth = HMEngine::UI::Font::SplitString(words[8], '=');
		HMEngine::UI::Font::CheckForError(smooth.size() != 2, "INVALID smooth PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> aa = HMEngine::UI::Font::SplitString(words[9], '=');
		HMEngine::UI::Font::CheckForError(aa.size() != 2, "INVALID aa PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> padding = HMEngine::UI::Font::SplitString(words[10], '=');
		HMEngine::UI::Font::CheckForError(padding.size() != 2, "INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> spacing = HMEngine::UI::Font::SplitString(words[11], '=');
		HMEngine::UI::Font::CheckForError(spacing.size() != 2, "INVALID spacing PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

		this->InitInfoHeader(face[1], size[1], bold[1], italic[1], charset[1], unicode[1], stretchH[1], smooth[1], aa[1], padding[1], spacing[1]);
	}
	else if (words[0] == "common")
	{
		HMEngine::UI::Font::CheckForError(words.size() != 7, "INVALID common TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);

		/* Gets all parameters from the common tag in .fnt file format and check their propriety */
		std::vector<std::string> lineHeight = HMEngine::UI::Font::SplitString(words[1], '=');
		HMEngine::UI::Font::CheckForError(lineHeight.size() != 2, "INVALID lineHeight PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> base = HMEngine::UI::Font::SplitString(words[2], '=');
		HMEngine::UI::Font::CheckForError(base.size() != 2, "INVALID base PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> scaleW = HMEngine::UI::Font::SplitString(words[3], '=');
		HMEngine::UI::Font::CheckForError(scaleW.size() != 2, "INVALID scaleW PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> scaleH = HMEngine::UI::Font::SplitString(words[4], '=');
		HMEngine::UI::Font::CheckForError(scaleH.size() != 2, "INVALID scaleH PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> pages = HMEngine::UI::Font::SplitString(words[5], '=');
		HMEngine::UI::Font::CheckForError(pages.size() != 2, "INVALID pages PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> packed = HMEngine::UI::Font::SplitString(words[6], '=');
		HMEngine::UI::Font::CheckForError(packed.size() != 2, "INVALID packed PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

		this->InitCommonHeader(lineHeight[1], base[1], scaleW[1], scaleH[1], pages[1], packed[1]);
	}
	else if (words[0] == "page")
	{
		HMEngine::UI::Font::CheckForError(words.size() != 3, "INVALID page TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);

		/* Gets all parameters from the page tag in .fnt file format and check their propriety */
		std::vector<std::string> id = HMEngine::UI::Font::SplitString(words[1], '=');
		HMEngine::UI::Font::CheckForError(id.size() != 2, "INVALID id PARMETER IN page TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
		std::vector<std::string> file = HMEngine::UI::Font::SplitString(words[2], '=');
		HMEngine::UI::Font::CheckForError(file.size() != 2, "INVALID file PARMETER IN page TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

		this->InitPageHeader(id[1], file[1]);
	}
	else if (words[0] == "chars")
	{
		HMEngine::UI::Font::CheckForError(words.size() != 2, "INVALID chars TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);

		/* Gets all parameters from the chars tag in .fnt file format and check their propriety */
		std::vector<std::string> count = HMEngine::UI::Font::SplitString(words[1], '=');
		HMEngine::UI::Font::CheckForError(count.size() != 2, "INVALID count PARMETER IN chars TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

		this->InitCharsHeader(count[1]);
	}
	else if (words[0] == "kernings")
	{
		HMEngine::UI::Font::CheckForError(words.size() != 2, "INVALID kernings TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);

		/* Gets all parameters from the kernings tag in .fnt file format and check their propriety */
		std::vector<std::string> count = HMEngine::UI::Font::SplitString(words[1], '=');
		HMEngine::UI::Font::CheckForError(count.size() != 2, "INVALID count PARMETER IN kernings TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

		this->InitKerningsHeader(count[1]);
	}
}

void HMEngine::UI::Font::InitInfoHeader(const std::string& face, const std::string& size, const std::string& bold, const std::string& italic,
	const std::string& charset, const std::string& unicode, const std::string& stretchH, const std::string& smooth, const std::string& aa,
	const std::string& padding, const std::string& spacing)
{
	std::string tmpFace = face;
	tmpFace.erase(std::remove_if(tmpFace.begin(), tmpFace.end(), [](char c) {return c == '\"'; }), tmpFace.end());
	this->_fontFile.info.face = tmpFace;

	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.info.size, size))
		HMEngine::Core::Utilities::ThrowException("INVALID size PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	HMEngine::UI::Font::CheckForError(bold.empty(), "INVALID bold PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	HMEngine::UI::Font::StringToBool(this->_fontFile.info.bold, bold);

	HMEngine::UI::Font::CheckForError(italic.empty(), "INVALID italic PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	HMEngine::UI::Font::StringToBool(this->_fontFile.info.italic, italic);

	std::string tmpCharset = charset;
	tmpCharset.erase(std::remove_if(tmpCharset.begin(), tmpCharset.end(), [](char c) {return c == '\"'; }), tmpCharset.end());
	this->_fontFile.info.charset = tmpCharset;

	HMEngine::UI::Font::CheckForError(unicode.empty(), "INVALID unicode PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	HMEngine::UI::Font::StringToBool(this->_fontFile.info.unicode, unicode);

	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.info.stretchH, stretchH))
		HMEngine::Core::Utilities::ThrowException("INVALID stretchH PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	HMEngine::UI::Font::CheckForError(smooth.empty(), "INVALID italic PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	HMEngine::UI::Font::StringToBool(this->_fontFile.info.smooth, smooth);

	if (!HMEngine::UI::Font::StringToFloat(this->_fontFile.info.aa, aa))
		HMEngine::Core::Utilities::ThrowException("INVALID aa PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	std::vector<std::string> tmpPadding = HMEngine::UI::Font::SplitString(padding, ',');
	HMEngine::UI::Font::CheckForError(tmpPadding.size() != 4, "INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	int x, y, z, w;
	if (!HMEngine::UI::Font::StringToInt(x, tmpPadding[0]))
		HMEngine::Core::Utilities::ThrowException("INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	if (!HMEngine::UI::Font::StringToInt(y, tmpPadding[1]))
		HMEngine::Core::Utilities::ThrowException("INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	if (!HMEngine::UI::Font::StringToInt(z, tmpPadding[2]))
		HMEngine::Core::Utilities::ThrowException("INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	if (!HMEngine::UI::Font::StringToInt(w, tmpPadding[3]))
		HMEngine::Core::Utilities::ThrowException("INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	this->_fontFile.info.padding = glm::vec4(x, y, z, w);

	std::vector<std::string> tmpSpacing = HMEngine::UI::Font::SplitString(spacing, ',');
	HMEngine::UI::Font::CheckForError(tmpSpacing.size() != 2, "INVALID spacing PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	if (!HMEngine::UI::Font::StringToInt(x, tmpSpacing[0]))
		HMEngine::Core::Utilities::ThrowException("INVALID spacing PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	if (!HMEngine::UI::Font::StringToInt(y, tmpSpacing[1]))
		HMEngine::Core::Utilities::ThrowException("INVALID spacing PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
	this->_fontFile.info.spacing = glm::vec2(x, y);
}

void HMEngine::UI::Font::InitCommonHeader(const std::string& lineHeight, const std::string& base, const std::string& scaleW, const std::string& scaleH,
	const std::string& pages, const std::string& packed)
{
	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.common.lineHeight, lineHeight))
		HMEngine::Core::Utilities::ThrowException("INVALID lineHeight PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.common.base, base))
		HMEngine::Core::Utilities::ThrowException("INVALID base PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.common.scaleW, scaleW))
		HMEngine::Core::Utilities::ThrowException("INVALID scaleW PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.common.scaleH, scaleH))
		HMEngine::Core::Utilities::ThrowException("INVALID scaleH PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.common.pages, pages))
		HMEngine::Core::Utilities::ThrowException("INVALID pages PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.common.packed, packed))
		HMEngine::Core::Utilities::ThrowException("INVALID packed PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
}

void HMEngine::UI::Font::InitPageHeader(const std::string& id, const std::string& file)
{
	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.page.id, id))
		HMEngine::Core::Utilities::ThrowException("INVALID id PARMETER IN page TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	std::string tmpFile = file;
	tmpFile.erase(std::remove_if(tmpFile.begin(), tmpFile.end(), [](char c) {return c == '\"'; }), tmpFile.end());
	this->_fontFile.page.file = tmpFile;
}

void HMEngine::UI::Font::InitCharsHeader(const std::string& count)
{
	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.chars.count, count))
		HMEngine::Core::Utilities::ThrowException("INVALID count PARMETER IN chars TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
}

void HMEngine::UI::Font::InitKerningsHeader(const std::string& count)
{
	if (!HMEngine::UI::Font::StringToInt(this->_fontFile.kernings.count, count))
		HMEngine::Core::Utilities::ThrowException("INVALID count PARMETER IN kernings TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
}

void HMEngine::UI::Font::AddCharacter(const std::string& id, const std::string& x, const std::string& y, const std::string& width, const std::string& height, 
	const std::string& xOffset, const std::string& yOffset, const std::string& xAdvance, const std::string& page, const std::string& chnl)
{
	HMEngine::UI::Font::BMFontCharacter character;

	if (!HMEngine::UI::Font::StringToInt(character.id, id))
		HMEngine::Core::Utilities::ThrowException("INVALID id PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(character.x, x))
		HMEngine::Core::Utilities::ThrowException("INVALID x PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(character.y, y))
		HMEngine::Core::Utilities::ThrowException("INVALID y PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(character.height, height))
		HMEngine::Core::Utilities::ThrowException("INVALID height PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(character.xOffset, xOffset))
		HMEngine::Core::Utilities::ThrowException("INVALID xOffset PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(character.yOffset, yOffset))
		HMEngine::Core::Utilities::ThrowException("INVALID yOffset PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(character.xAdvance, xAdvance))
		HMEngine::Core::Utilities::ThrowException("INVALID xAdvance PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(character.page, page))
		HMEngine::Core::Utilities::ThrowException("INVALID page PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(character.chnl, chnl))
		HMEngine::Core::Utilities::ThrowException("INVALID chnl PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	this->_fontFile.charactersMap[character.id] = character;
}

void HMEngine::UI::Font::AddKerning(const std::string& first, const std::string& second, const std::string& amount)
{
	HMEngine::UI::Font::BMFontKerning kerning;

	if (!HMEngine::UI::Font::StringToInt(kerning.first, first))
		HMEngine::Core::Utilities::ThrowException("INVALID first PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(kerning.second, second))
		HMEngine::Core::Utilities::ThrowException("INVALID second PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	if (!HMEngine::UI::Font::StringToInt(kerning.amount, amount))
		HMEngine::Core::Utilities::ThrowException("INVALID amount PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);

	this->_fontFile.kerningsVector.push_back(kerning);
}