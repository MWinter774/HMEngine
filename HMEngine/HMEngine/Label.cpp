#include "Label.h"
#include "OpenGLQuad.h"
#include "GameSettings.h"
#include <vector>
#include "Line.h"

HMEngine::UI::Label::Label(const std::string& name, const glm::vec2& position, const std::string& text, const HMEngine::UI::Font& font, const glm::vec3& color,
	float fontSize) : HMEngine::UI::Quad(name, font.GetFntTexturePath(), position, glm::vec2(1, 1), false), _text(text), _font(font), _fontSize(fontSize),
	_color(color)
{
	this->InitializeEvents<Label>(this);
	this->_color /= 255;

	std::vector<glm::vec2> vertices, uvs;
	HMEngine::UI::Label::CalculateMeshData(vertices, uvs, this->_text, this->_font, 1.0f, this->_fontSize);

	this->SetVertices(vertices);
	this->SetUVs(uvs);
}

HMEngine::UI::Label::Label(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& text,
	const HMEngine::UI::Font& font, const glm::vec3& color) : HMEngine::UI::Quad(name, font.GetFntTexturePath(), position, scale, false),
	_text(text), _font(font), _color(color)
{
	this->InitializeEvents<Label>(this);
	this->_color /= 255;

	std::vector<glm::vec2> vertices, uvs;
	HMEngine::UI::Label::CalculateMeshData(vertices, uvs, this->_text, this->_font, 1.0f, this->_fontSize);
	
	this->SetVertices(vertices);
	this->SetUVs(uvs);
}

HMEngine::UI::Label::~Label()
{
}

HMEngine::UI::Label::Label(const HMEngine::UI::Label& other) : HMEngine::UI::Quad(other), _text(other._text), _font(other._font), _fontSize(other._fontSize),
_color(other._color)
{
	this->InitializeEvents<Label>(this);
}

HMEngine::UI::Label& HMEngine::UI::Label::operator=(const HMEngine::UI::Label& other)
{
	if (this != &other)
	{
		HMEngine::UI::Quad::operator=(other);
		this->_text = other._text;
		this->_font = other._font;
		this->_fontSize = other._fontSize;
		this->_color = other._color;
		this->InitializeEvents<Label>(this);
	}

	return *this;
}

void HMEngine::UI::Label::Draw() const
{
	this->BindTexture();
	this->_openglQuad->Draw(GL_TRIANGLES);
}

void HMEngine::UI::Label::AddVerticesForCharacter(std::vector<glm::vec2>& vertices, const HMEngine::Core::FNTFile::BMFontCharacter& character,
	float cursorX, float cursorY, float fontSize)
{
	float x = cursorX + (character.xOffset * fontSize);
	float y = cursorY + (character.yOffset * fontSize);
	float maxX = x + (character.quadWidth * fontSize);
	float maxY = y + (character.quadHeight * fontSize);
	float properX = (2 * x) - 1;
	float properY = (-2 * y) + 1;
	float properMaxX = (2 * maxX) - 1;
	float properMaxY = (-2 * maxY) + 1;
	HMEngine::UI::Label::AddVertices(vertices, properX, properY, properMaxX, properMaxY);
}

void HMEngine::UI::Label::AddVertices(std::vector<glm::vec2>& vertices, float x, float y, float maxX, float maxY)
{
	vertices.push_back(glm::vec2(x, y));
	vertices.push_back(glm::vec2(x, maxY));
	vertices.push_back(glm::vec2(maxX, maxY));
	vertices.push_back(glm::vec2(maxX, maxY));
	vertices.push_back(glm::vec2(maxX, y));
	vertices.push_back(glm::vec2(x, y));
}

void HMEngine::UI::Label::AddUVs(std::vector<glm::vec2>& uvs, float x, float y, float maxX, float maxY)
{
	uvs.push_back(glm::vec2(x, y));
	uvs.push_back(glm::vec2(x, maxY));
	uvs.push_back(glm::vec2(maxX, maxY));
	uvs.push_back(glm::vec2(maxX, maxY));
	uvs.push_back(glm::vec2(maxX, y));
	uvs.push_back(glm::vec2(x, y));
}

void HMEngine::UI::Label::CalculateMeshData(std::vector<glm::vec2>& vertices, std::vector<glm::vec2>& uvs, 
	const std::string& text, const HMEngine::UI::Font& font, float fontSize, float maxLineSize)
{
	float cursorX = 0;
	float cursorY = 0;

	std::vector<HMEngine::Core::Font::Line> lines;
	HMEngine::UI::Label::CreateStructure(lines, text, font, fontSize, maxLineSize);

	HMEngine::UI::Label::GetVerticesAndUVs(text, font, fontSize, maxLineSize, lines, vertices, uvs);
}

void HMEngine::UI::Label::CreateStructure(std::vector<HMEngine::Core::Font::Line>& lines, const std::string& text,
	const HMEngine::UI::Font& font, float fontSize, float maxLineSize)
{
	HMEngine::Core::Font::Line currentLine = HMEngine::Core::Font::Line(font.GetSpaceWidth(), fontSize, maxLineSize);
	HMEngine::Core::Font::Word currentWord = HMEngine::Core::Font::Word(fontSize);
	for (const auto& character : text)
	{
		if (character == ' ')
		{
			bool added = currentLine.AttemptToAddWord(currentWord);
			if (!added) 
			{
				lines.push_back(currentLine);
				currentLine = HMEngine::Core::Font::Line(font.GetSpaceWidth(), fontSize, maxLineSize);
				currentLine.AttemptToAddWord(currentWord);
			}
			currentWord = HMEngine::Core::Font::Word(fontSize);
			continue;
		}
		HMEngine::Core::FNTFile::BMFontCharacter bmfCharacter = font[character];
		currentWord.AddCharacter(bmfCharacter);
	}

	/* Complete Structure */
	bool added = currentLine.AttemptToAddWord(currentWord);
	if (!added) {
		lines.push_back(currentLine);
		currentLine = HMEngine::Core::Font::Line(font.GetSpaceWidth(), fontSize, maxLineSize);
		currentLine.AttemptToAddWord(currentWord);
	}
	lines.push_back(currentLine);
}

void HMEngine::UI::Label::GetVerticesAndUVs(const std::string& text, const HMEngine::UI::Font& font, float fontSize, float maxLineSize, 
	const std::vector<HMEngine::Core::Font::Line> lines, std::vector<glm::vec2>& vertices, std::vector<glm::vec2>& uvs)
{
	float curserX = 0.0f;
	float curserY = 0.0f;

	for (HMEngine::Core::Font::Line line : lines) {
		if (/*text.isCentered()*/ false) {
			curserX = (line.GetMaxLineLength() - line.GetCurrentLineLength()) / 2;
		}
		for (HMEngine::Core::Font::Word word : line.GetWords()) {
			for (HMEngine::Core::FNTFile::BMFontCharacter letter : word.GetCharacters()) {
				HMEngine::UI::Label::AddVerticesForCharacter(vertices, letter, curserX, curserY, fontSize);
				HMEngine::UI::Label::AddUVs(uvs, letter.xTextureCoordiante, letter.yTextureCoordiante, letter.xMaxTextureCoordinate, letter.yMaxTextureCoordinate);
				curserX += letter.xAdvance * fontSize;
			}
			curserX += font.GetSpaceWidth() * fontSize;
		}
		curserX = 0;
		curserY += 0.03f * fontSize;
	}
}

void HMEngine::UI::Label::UpdateText()
{
	std::vector<glm::vec2> vertices, uvs;
	HMEngine::UI::Label::CalculateMeshData(vertices, uvs, this->_text, this->_font, 1.0f, this->_fontSize);

	this->SetVertices(vertices);
	this->SetUVs(uvs);
	this->_openglQuad->Initialize();
}