#include "FNTFile.h"
#include "Utilities.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "GameSettings.h"



//const int HMEngine::Core::FNTFile::DESIRED_PADDING = 3;
//const unsigned int& HMEngine::Core::FNTFile::windowWidth = HMEngine::GameSettings::GetWindowWidth();
//const unsigned int& HMEngine::Core::FNTFile::windowHeight = HMEngine::GameSettings::GetWindowHeight();
//const float HMEngine::Core::FNTFile::LINE_HEIGHT = 0.03f;
//
//HMEngine::Core::FNTFile::FNTFile(const std::string& fntFilePath) : _fntFilePath(fntFilePath)
//{
//	std::ifstream fntFile(this->_fntFilePath);
//	if (!fntFile.is_open())
//	{
//		HMEngine::Core::Utilities::ThrowException("FONT FILE: " + fntFilePath + " DOESN'T EXIST!");
//	}
//	std::vector<std::string>* lines = HMEngine::Core::FNTFile::ReadLines(fntFile);
//	std::vector<std::string> words;
//	for (auto& line : *lines)
//	{
//		words = HMEngine::Core::FNTFile::SplitString(line, ' ');
//
//		this->ProcessLine(words);
//	}
//
//	delete lines;
//}
//
//HMEngine::Core::FNTFile::~FNTFile()
//{
//}
//
//HMEngine::Core::FNTFile::BMFontCharacter HMEngine::Core::FNTFile::GetCharacter(int asciiCode)
//{
//	auto& character = this->_charactersMap.find(asciiCode);
//	if (character == this->_charactersMap.end())
//	{
//		HMEngine::Core::Utilities::ThrowException("ASCII CODE " + std::to_string(asciiCode) + " DOESN'T EXIST IN FONT!\nTHE FONT: " + this->_fntFilePath);
//	}
//	return (*character).second;
//}
//
//float HMEngine::Core::FNTFile::AspectRatio()
//{
//	return float(HMEngine::Core::FNTFile::windowWidth) / HMEngine::Core::FNTFile::windowHeight;
//}
//
//std::vector<std::string>* HMEngine::Core::FNTFile::ReadLines(std::ifstream& file)
//{
//	std::vector<std::string>* lines = new std::vector<std::string>();
//	std::string currLine;
//
//	while (std::getline(file, currLine))
//	{
//		lines->push_back(currLine);
//	}
//
//	return lines;
//}
//
//std::vector<std::string> HMEngine::Core::FNTFile::SplitString(const std::string& string, char delimiter)
//{
//	std::vector<std::string> strings = std::vector<std::string>();
//	std::string currWord;
//	std::istringstream stringStream(string);
//
//	while (std::getline(stringStream, currWord, delimiter))
//	{
//		if (!currWord.empty())
//			strings.push_back(currWord);
//	}
//
//	return strings;
//}
//
//void HMEngine::Core::FNTFile::CheckForError(bool condition, const std::string & errorMessage)
//{
//	if (condition)
//		HMEngine::Core::Utilities::ThrowException(errorMessage);
//}
//
//bool HMEngine::Core::FNTFile::StringToInt(int& data, const std::string& toConvert)
//{
//	try
//	{
//		data = std::stoi(toConvert);
//	}
//	catch (...)
//	{
//		data = -1;
//		return false;
//	}
//	return true;
//}
//
//bool HMEngine::Core::FNTFile::StringToFloat(float& data, const std::string& toConvert)
//{
//	try
//	{
//		data = std::stof(toConvert);
//	}
//	catch (...)
//	{
//		data = -1;
//		return false;
//	}
//	return true;
//}
//
//void HMEngine::Core::FNTFile::StringToBool(bool& data, const std::string& toConvert)
//{
//	data = toConvert[0] == '1';
//}
//
//void HMEngine::Core::FNTFile::ProcessLine(const std::vector<std::string>& words)
//{
//	HMEngine::Core::FNTFile::CheckForError(words.size() == 0, "INVALID .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);
//
//	if (words[0] == "char")
//	{
//		HMEngine::Core::FNTFile::CheckForError(words.size() != 11, "INVALID char TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);
//
//		/* Gets all parameters from the char tag in .fnt file format and check their propriety */
//		std::vector<std::string> id = HMEngine::Core::FNTFile::SplitString(words[1], '=');
//		HMEngine::Core::FNTFile::CheckForError(id.size() != 2, "INVALID id PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> x = HMEngine::Core::FNTFile::SplitString(words[2], '=');
//		HMEngine::Core::FNTFile::CheckForError(x.size() != 2, "INVALID x PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> y = HMEngine::Core::FNTFile::SplitString(words[3], '=');
//		HMEngine::Core::FNTFile::CheckForError(y.size() != 2, "INVALID y PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> width = HMEngine::Core::FNTFile::SplitString(words[4], '=');
//		HMEngine::Core::FNTFile::CheckForError(width.size() != 2, "INVALID width PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> height = HMEngine::Core::FNTFile::SplitString(words[5], '=');
//		HMEngine::Core::FNTFile::CheckForError(height.size() != 2, "INVALID height PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> xOffset = HMEngine::Core::FNTFile::SplitString(words[6], '=');
//		HMEngine::Core::FNTFile::CheckForError(xOffset.size() != 2, "INVALID xOffset PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> yOffset = HMEngine::Core::FNTFile::SplitString(words[7], '=');
//		HMEngine::Core::FNTFile::CheckForError(yOffset.size() != 2, "INVALID yOffset PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> xAdvance = HMEngine::Core::FNTFile::SplitString(words[8], '=');
//		HMEngine::Core::FNTFile::CheckForError(xAdvance.size() != 2, "INVALID xAdvance PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> page = HMEngine::Core::FNTFile::SplitString(words[9], '=');
//		HMEngine::Core::FNTFile::CheckForError(page.size() != 2, "INVALID page PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> chnl = HMEngine::Core::FNTFile::SplitString(words[10], '=');
//		HMEngine::Core::FNTFile::CheckForError(chnl.size() != 2, "INVALID chnl PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//		this->AddCharacter(id[1], x[1], y[1], width[1], height[1], xOffset[1], yOffset[1], xAdvance[1], page[1], chnl[1]);
//	}
//	else if (words[0] == "kerning")
//	{
//		HMEngine::Core::FNTFile::CheckForError(words.size() != 4, "INVALID kerning TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);
//
//		/* Gets all parameters from the kerning tag in .fnt file format and check their propriety */
//		std::vector<std::string> first = HMEngine::Core::FNTFile::SplitString(words[1], '=');
//		HMEngine::Core::FNTFile::CheckForError(first.size() != 2, "INVALID first PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> second = HMEngine::Core::FNTFile::SplitString(words[2], '=');
//		HMEngine::Core::FNTFile::CheckForError(second.size() != 2, "INVALID second PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> amount = HMEngine::Core::FNTFile::SplitString(words[3], '=');
//		HMEngine::Core::FNTFile::CheckForError(amount.size() != 2, "INVALID amount PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//		this->AddKerning(first[1], second[1], amount[1]);
//	}
//	else if (words[0] == "info")
//	{
//		HMEngine::Core::FNTFile::CheckForError(words.size() != 12, "INVALID info TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);
//
//		/* Gets all parameters from the info tag in .fnt file format and check their propriety */
//		std::vector<std::string> face = HMEngine::Core::FNTFile::SplitString(words[1], '=');
//		HMEngine::Core::FNTFile::CheckForError(face.size() != 2, "INVALID face PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> size = HMEngine::Core::FNTFile::SplitString(words[2], '=');
//		HMEngine::Core::FNTFile::CheckForError(size.size() != 2, "INVALID size PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> bold = HMEngine::Core::FNTFile::SplitString(words[3], '=');
//		HMEngine::Core::FNTFile::CheckForError(bold.size() != 2, "INVALID bold PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> italic = HMEngine::Core::FNTFile::SplitString(words[4], '=');
//		HMEngine::Core::FNTFile::CheckForError(italic.size() != 2, "INVALID italic PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> charset = HMEngine::Core::FNTFile::SplitString(words[5], '=');
//		HMEngine::Core::FNTFile::CheckForError(charset.size() != 2, "INVALID charset PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> unicode = HMEngine::Core::FNTFile::SplitString(words[6], '=');
//		HMEngine::Core::FNTFile::CheckForError(unicode.size() != 2, "INVALID unicode PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> stretchH = HMEngine::Core::FNTFile::SplitString(words[7], '=');
//		HMEngine::Core::FNTFile::CheckForError(stretchH.size() != 2, "INVALID stretchH PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> smooth = HMEngine::Core::FNTFile::SplitString(words[8], '=');
//		HMEngine::Core::FNTFile::CheckForError(smooth.size() != 2, "INVALID smooth PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> aa = HMEngine::Core::FNTFile::SplitString(words[9], '=');
//		HMEngine::Core::FNTFile::CheckForError(aa.size() != 2, "INVALID aa PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> padding = HMEngine::Core::FNTFile::SplitString(words[10], '=');
//		HMEngine::Core::FNTFile::CheckForError(padding.size() != 2, "INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> spacing = HMEngine::Core::FNTFile::SplitString(words[11], '=');
//		HMEngine::Core::FNTFile::CheckForError(spacing.size() != 2, "INVALID spacing PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//		this->InitInfoHeader(face[1], size[1], bold[1], italic[1], charset[1], unicode[1], stretchH[1], smooth[1], aa[1], padding[1], spacing[1]);
//	}
//	else if (words[0] == "common")
//	{
//		HMEngine::Core::FNTFile::CheckForError(words.size() != 7, "INVALID common TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);
//
//		/* Gets all parameters from the common tag in .fnt file format and check their propriety */
//		std::vector<std::string> lineHeight = HMEngine::Core::FNTFile::SplitString(words[1], '=');
//		HMEngine::Core::FNTFile::CheckForError(lineHeight.size() != 2, "INVALID lineHeight PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> base = HMEngine::Core::FNTFile::SplitString(words[2], '=');
//		HMEngine::Core::FNTFile::CheckForError(base.size() != 2, "INVALID base PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> scaleW = HMEngine::Core::FNTFile::SplitString(words[3], '=');
//		HMEngine::Core::FNTFile::CheckForError(scaleW.size() != 2, "INVALID scaleW PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> scaleH = HMEngine::Core::FNTFile::SplitString(words[4], '=');
//		HMEngine::Core::FNTFile::CheckForError(scaleH.size() != 2, "INVALID scaleH PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> pages = HMEngine::Core::FNTFile::SplitString(words[5], '=');
//		HMEngine::Core::FNTFile::CheckForError(pages.size() != 2, "INVALID pages PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> packed = HMEngine::Core::FNTFile::SplitString(words[6], '=');
//		HMEngine::Core::FNTFile::CheckForError(packed.size() != 2, "INVALID packed PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//		this->InitCommonHeader(lineHeight[1], base[1], scaleW[1], scaleH[1], pages[1], packed[1]);
//	}
//	else if (words[0] == "page")
//	{
//		HMEngine::Core::FNTFile::CheckForError(words.size() != 3, "INVALID page TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);
//
//		/* Gets all parameters from the page tag in .fnt file format and check their propriety */
//		std::vector<std::string> id = HMEngine::Core::FNTFile::SplitString(words[1], '=');
//		HMEngine::Core::FNTFile::CheckForError(id.size() != 2, "INVALID id PARMETER IN page TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//		std::vector<std::string> file = HMEngine::Core::FNTFile::SplitString(words[2], '=');
//		HMEngine::Core::FNTFile::CheckForError(file.size() != 2, "INVALID file PARMETER IN page TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//		this->InitPageHeader(id[1], file[1]);
//	}
//	else if (words[0] == "chars")
//	{
//		HMEngine::Core::FNTFile::CheckForError(words.size() != 2, "INVALID chars TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);
//
//		/* Gets all parameters from the chars tag in .fnt file format and check their propriety */
//		std::vector<std::string> count = HMEngine::Core::FNTFile::SplitString(words[1], '=');
//		HMEngine::Core::FNTFile::CheckForError(count.size() != 2, "INVALID count PARMETER IN chars TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//		this->InitCharsHeader(count[1]);
//	}
//	else if (words[0] == "kernings")
//	{
//		HMEngine::Core::FNTFile::CheckForError(words.size() != 2, "INVALID kernings TAG IN .fnt FILE FORMAT!\nThe File: " + this->_fntFilePath);
//
//		/* Gets all parameters from the kernings tag in .fnt file format and check their propriety */
//		std::vector<std::string> count = HMEngine::Core::FNTFile::SplitString(words[1], '=');
//		HMEngine::Core::FNTFile::CheckForError(count.size() != 2, "INVALID count PARMETER IN kernings TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//		this->InitKerningsHeader(count[1]);
//	}
//}
//
//void HMEngine::Core::FNTFile::InitInfoHeader(const std::string& face, const std::string& size, const std::string& bold, const std::string& italic,
//	const std::string& charset, const std::string& unicode, const std::string& stretchH, const std::string& smooth, const std::string& aa,
//	const std::string& padding, const std::string& spacing)
//{
//	std::string tmpFace = face;
//	tmpFace.erase(std::remove_if(tmpFace.begin(), tmpFace.end(), [](char c) {return c == '\"'; }), tmpFace.end());
//	this->_info.face = tmpFace;
//
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_info.size, size))
//		HMEngine::Core::Utilities::ThrowException("INVALID size PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	HMEngine::Core::FNTFile::CheckForError(bold.empty(), "INVALID bold PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	HMEngine::Core::FNTFile::StringToBool(this->_info.bold, bold);
//
//	HMEngine::Core::FNTFile::CheckForError(italic.empty(), "INVALID italic PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	HMEngine::Core::FNTFile::StringToBool(this->_info.italic, italic);
//
//	std::string tmpCharset = charset;
//	tmpCharset.erase(std::remove_if(tmpCharset.begin(), tmpCharset.end(), [](char c) {return c == '\"'; }), tmpCharset.end());
//	this->_info.charset = tmpCharset;
//
//	HMEngine::Core::FNTFile::CheckForError(unicode.empty(), "INVALID unicode PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	HMEngine::Core::FNTFile::StringToBool(this->_info.unicode, unicode);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_info.stretchH, stretchH))
//		HMEngine::Core::Utilities::ThrowException("INVALID stretchH PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	HMEngine::Core::FNTFile::CheckForError(smooth.empty(), "INVALID italic PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	HMEngine::Core::FNTFile::StringToBool(this->_info.smooth, smooth);
//
//	if (!HMEngine::Core::FNTFile::StringToFloat(this->_info.aa, aa))
//		HMEngine::Core::Utilities::ThrowException("INVALID aa PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	std::vector<std::string> tmpPadding = HMEngine::Core::FNTFile::SplitString(padding, ',');
//	HMEngine::Core::FNTFile::CheckForError(tmpPadding.size() != 4, "INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	int x, y, z, w;
//	if (!HMEngine::Core::FNTFile::StringToInt(x, tmpPadding[0]))
//		HMEngine::Core::Utilities::ThrowException("INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	if (!HMEngine::Core::FNTFile::StringToInt(y, tmpPadding[1]))
//		HMEngine::Core::Utilities::ThrowException("INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	if (!HMEngine::Core::FNTFile::StringToInt(z, tmpPadding[2]))
//		HMEngine::Core::Utilities::ThrowException("INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	if (!HMEngine::Core::FNTFile::StringToInt(w, tmpPadding[3]))
//		HMEngine::Core::Utilities::ThrowException("INVALID padding PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	this->_info.padding = glm::vec4(x, y, z, w);
//	this->_info.paddingWidth = this->_info.padding[this->leftPadding] + this->_info.padding[this->rightPadding];
//	this->_info.paddingHeight = this->_info.padding[this->upPadding] + this->_info.padding[this->downPadding];
//
//	std::vector<std::string> tmpSpacing = HMEngine::Core::FNTFile::SplitString(spacing, ',');
//	HMEngine::Core::FNTFile::CheckForError(tmpSpacing.size() != 2, "INVALID spacing PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	if (!HMEngine::Core::FNTFile::StringToInt(x, tmpSpacing[0]))
//		HMEngine::Core::Utilities::ThrowException("INVALID spacing PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	if (!HMEngine::Core::FNTFile::StringToInt(y, tmpSpacing[1]))
//		HMEngine::Core::Utilities::ThrowException("INVALID spacing PARMETER IN info TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//	this->_info.spacing = glm::vec2(x, y);
//}
//
//void HMEngine::Core::FNTFile::InitCommonHeader(const std::string& lineHeight, const std::string& base, const std::string& scaleW, const std::string& scaleH,
//	const std::string& pages, const std::string& packed)
//{
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_common.lineHeight, lineHeight))
//		HMEngine::Core::Utilities::ThrowException("INVALID lineHeight PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_common.base, base))
//		HMEngine::Core::Utilities::ThrowException("INVALID base PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_common.scaleW, scaleW))
//		HMEngine::Core::Utilities::ThrowException("INVALID scaleW PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_common.scaleH, scaleH))
//		HMEngine::Core::Utilities::ThrowException("INVALID scaleH PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_common.pages, pages))
//		HMEngine::Core::Utilities::ThrowException("INVALID pages PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_common.packed, packed))
//		HMEngine::Core::Utilities::ThrowException("INVALID packed PARMETER IN common TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	int lineHeightPixels = this->_common.lineHeight - this->_info.paddingHeight;
//	this->_verticalPerPixelSize = HMEngine::Core::FNTFile::LINE_HEIGHT / lineHeightPixels;
//	this->_horizontalPerPixelSize = this->_verticalPerPixelSize / HMEngine::Core::FNTFile::AspectRatio();
//}
//
//void HMEngine::Core::FNTFile::InitPageHeader(const std::string& id, const std::string& file)
//{
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_page.id, id))
//		HMEngine::Core::Utilities::ThrowException("INVALID id PARMETER IN page TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	std::string tmpFile = file;
//	tmpFile.erase(std::remove_if(tmpFile.begin(), tmpFile.end(), [](char c) {return c == '\"'; }), tmpFile.end());
//	this->_page.file = tmpFile;
//}
//
//void HMEngine::Core::FNTFile::InitCharsHeader(const std::string& count)
//{
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_chars.count, count))
//		HMEngine::Core::Utilities::ThrowException("INVALID count PARMETER IN chars TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//}
//
//void HMEngine::Core::FNTFile::InitKerningsHeader(const std::string& count)
//{
//	if (!HMEngine::Core::FNTFile::StringToInt(this->_kernings.count, count))
//		HMEngine::Core::Utilities::ThrowException("INVALID count PARMETER IN kernings TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//}
//
//void HMEngine::Core::FNTFile::AddCharacter(const std::string& id, const std::string& x, const std::string& y, const std::string& width, const std::string& height,
//	const std::string& xOffset, const std::string& yOffset, const std::string& xAdvance, const std::string& page, const std::string& chnl)
//{
//	HMEngine::Core::FNTFile::BMFontCharacter character;
//
//	/* Loads character data in pixels */
//	if (!HMEngine::Core::FNTFile::StringToInt(character.id, id))
//		HMEngine::Core::Utilities::ThrowException("INVALID id PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToFloat(character.xTextureCoordiante, x))
//		HMEngine::Core::Utilities::ThrowException("INVALID x PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToFloat(character.yTextureCoordiante, y))
//		HMEngine::Core::Utilities::ThrowException("INVALID y PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToFloat(character.textureWidth, width))
//		HMEngine::Core::Utilities::ThrowException("INVALID width PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToFloat(character.textureHeight, height))
//		HMEngine::Core::Utilities::ThrowException("INVALID height PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToFloat(character.xOffset, xOffset))
//		HMEngine::Core::Utilities::ThrowException("INVALID xOffset PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToFloat(character.yOffset, yOffset))
//		HMEngine::Core::Utilities::ThrowException("INVALID yOffset PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToFloat(character.xAdvance, xAdvance))
//		HMEngine::Core::Utilities::ThrowException("INVALID xAdvance PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(character.page, page))
//		HMEngine::Core::Utilities::ThrowException("INVALID page PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(character.chnl, chnl))
//		HMEngine::Core::Utilities::ThrowException("INVALID chnl PARMETER IN char TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	//this->_horizontalPerPixelSize = 0.0001896067373349928;
//	/* Converts character pixel data to screen-space */
//	//if (character.id == 72) {
//		character.xTextureCoordiante = (character.xTextureCoordiante + this->_info.padding[this->leftPadding] - HMEngine::Core::FNTFile::DESIRED_PADDING)
//			/ this->_common.scaleW;
//		character.yTextureCoordiante = (character.yTextureCoordiante + (this->_info.padding[this->upPadding] - HMEngine::Core::FNTFile::DESIRED_PADDING))
//			/ this->_common.scaleW;
//		float textureWidth = character.textureWidth - (this->_info.paddingWidth - (2 * HMEngine::Core::FNTFile::DESIRED_PADDING));
//		float textureHeight = character.textureHeight - ((this->_info.paddingHeight) - (2 * HMEngine::Core::FNTFile::DESIRED_PADDING));
//		character.quadWidth = textureWidth * this->_horizontalPerPixelSize;
//		character.quadHeight = textureHeight * this->_verticalPerPixelSize;
//		character.textureWidth = textureWidth / this->_common.scaleW;
//		character.textureHeight = textureHeight / this->_common.scaleW;
//		character.xOffset = (character.xOffset + this->_info.padding[this->leftPadding] - HMEngine::Core::FNTFile::DESIRED_PADDING) * this->_horizontalPerPixelSize;
//		character.yOffset = (character.yOffset + (this->_info.padding[this->upPadding] - HMEngine::Core::FNTFile::DESIRED_PADDING)) * this->_verticalPerPixelSize;
//		character.xAdvance = (character.xAdvance - this->_info.paddingWidth) * this->_horizontalPerPixelSize;
//		character.xMaxTextureCoordinate = character.xTextureCoordiante + character.textureWidth;
//		character.yMaxTextureCoordinate = character.yTextureCoordiante + character.textureHeight;
//
//		this->_charactersMap[character.id] = character;
//	//}
//}
//
//void HMEngine::Core::FNTFile::AddKerning(const std::string& first, const std::string& second, const std::string& amount)
//{
//	HMEngine::Core::FNTFile::BMFontKerning kerning;
//
//	if (!HMEngine::Core::FNTFile::StringToInt(kerning.first, first))
//		HMEngine::Core::Utilities::ThrowException("INVALID first PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(kerning.second, second))
//		HMEngine::Core::Utilities::ThrowException("INVALID second PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	if (!HMEngine::Core::FNTFile::StringToInt(kerning.amount, amount))
//		HMEngine::Core::Utilities::ThrowException("INVALID amount PARMETER IN kerning TAG IN .fnt FILE FORMAT\nThe File: " + this->_fntFilePath);
//
//	this->_kerningsVector.push_back(kerning);
//}

HMEngine::Core::FNTFile::FNTFile(const std::string& ttfFilePath) : _ttfFilePath(ttfFilePath)
{
	if (FT_Init_FreeType(&this->_fontLibrary))
		HMEngine::Core::Utilities::ThrowException("FreeType LIBRARY INITIALIZATION FAILED!");

	if (FT_New_Face(this->_fontLibrary, ttfFilePath.c_str(), 0, &this->_font))
		HMEngine::Core::Utilities::ThrowException("FAILED TO LOAD FONT " + ttfFilePath);

	FT_Set_Pixel_Sizes(this->_font, 0, 16); //SET FONT SIZE

	/* Generates the character of the font */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //Disable byte-alignment restriction
	for (unsigned char c = 0; c < 128; c++)
	{
		HMEngine::Core::FNTFile::Glyph glyph;

		/* Load character glyph */
		if (FT_Load_Char(this->_font, c, FT_LOAD_RENDER))
		{
			HMEngine::Core::Utilities::PrintDebugMessage(std::string("FAILED TO LOAD THE CHAR " + c) + " FOR THE FONT " + this->_ttfFilePath, "WARNING");
			continue;
		}

		/* Generates the texture for the glyph */
		GLuint textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->_font->glyph->bitmap.width, this->_font->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, this->_font->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		/* Initialize the glyph */
		glyph.textureId = textureId;
		glyph.size = glm::ivec2(this->_font->glyph->bitmap.width, this->_font->glyph->bitmap.rows);
		glyph.offsets = glm::ivec2(this->_font->glyph->bitmap_left, this->_font->glyph->bitmap_top);
		glyph.advance = this->_font->glyph->advance.x;

		/* Inserts to the glyphs map */
		this->_glyphs.insert(std::pair<char, HMEngine::Core::FNTFile::Glyph>(c, glyph));
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4); //Restores the default value

	FT_Done_Face(this->_font);
	FT_Done_FreeType(this->_fontLibrary);
}

HMEngine::Core::FNTFile::~FNTFile()
{
	for (auto& item : this->_glyphs)
	{
		glDeleteTextures(1, &item.second.textureId);
	}
}

HMEngine::Core::FNTFile::Glyph HMEngine::Core::FNTFile::GetCharacter(char c)
{
	auto& character = this->_glyphs.find(c);
	if (character == this->_glyphs.end())
	{
		HMEngine::Core::Utilities::ThrowException("CHARACTER " + std::to_string(c) + " DOESN'T EXIST IN FONT!\nTHE FONT: " + this->_ttfFilePath);
	}
	return this->_glyphs[c];
}
