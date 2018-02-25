#include "Label.h"
#include "OpenGLQuad.h"
#include "GameSettings.h"

HMEngine::UI::Label::Label(const std::string& name, const glm::vec2& position, const std::string& text, const HMEngine::UI::Font& font, const glm::vec3& color,
	float fontSize) : HMEngine::UI::Quad(name, font.GetFntTexturePath(), position, glm::vec2(1, 1), false), _text(text), _font(font), _fontSize(fontSize),
	_color(color)
{
	this->_color /= 255;
	this->InitLabel(false);
}

HMEngine::UI::Label::Label(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& text,
	const HMEngine::UI::Font& font, const glm::vec3& color, float fontSize) : HMEngine::UI::Quad(name, font.GetFntTexturePath(), position, scale, false),
	_text(text), _font(font), _fontSize(fontSize), _color(color)
{
	this->_color /= 255;
	this->InitLabel(true);
}

HMEngine::UI::Label::~Label()
{
}

HMEngine::UI::Label::Label(const HMEngine::UI::Label& other) : HMEngine::UI::Quad(other), _text(other._text), _font(other._font), _fontSize(other._fontSize),
_color(other._color)
{
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
	}

	return *this;
}

void HMEngine::UI::Label::Draw() const
{
	this->BindTexture();
	this->_openglQuad->Draw(GL_TRIANGLES);
}

/*
Calculates vertices and uvs of a label.
Input:
text - the text to calculate vertices and uvs
font - the font of the text
bottomLeft - bottom left corner of the label
fontSize - the size of the font
Output:
Tuple that the first element is vertices, second is uvs and the third is the dimension of the quad.
The quad's vertices are alligned so the label's position is in the center of the quad.
*/
std::tuple<std::vector<glm::vec2>, std::vector<glm::vec2>, glm::vec2> HMEngine::UI::Label::GetVerticesAndUVsFromText(const std::string& text,
	const HMEngine::UI::Font& font, const glm::vec2& bottomLeft, float fontSize)
{
	/*float cursorX = bottomLeft.x / HMEngine::GameSettings::GetWindowWidth();
	float cursorY = bottomLeft.y / HMEngine::GameSettings::GetWindowHeight();*/

	float cursorX = 0;
	float cursorY = 0;

	std::vector<glm::vec2> vertices = std::vector<glm::vec2>();
	std::vector<glm::vec2> uvs = std::vector<glm::vec2>();

	glm::vec2 dimensions;

	for (auto& character : text)
	{
		HMEngine::Core::FNTFile::BMFontCharacter fntChar = font[character];
		HMEngine::UI::Label::AddVerticesForCharacter(vertices, fntChar, cursorX, cursorY, fontSize);
		HMEngine::UI::Label::AddUVs(uvs, fntChar.xTextureCoordiante, fntChar.yTextureCoordiante, fntChar.xMaxTextureCoordinate, fntChar.yMaxTextureCoordinate);

		cursorX += fntChar.xAdvance * fontSize;
		dimensions.x += fntChar.xAdvance * fontSize;
		//dimensions.y = std::fmax(dimensions.y, fntChar.quadHeight * fontSize);
	}

	dimensions.y = 0.03f * fontSize;

	const float ASPECT_RATIO = float(HMEngine::GameSettings::GetWindowWidth()) / HMEngine::GameSettings::GetWindowHeight();
	float width = float(dimensions.x), height = float(dimensions.y);

	for (auto& vertex : vertices)
	{
		vertex.x -= width;
		vertex.y += height;
	}

	dimensions.x *= HMEngine::GameSettings::GetWindowWidth();
	dimensions.y *= HMEngine::GameSettings::GetWindowHeight();

	return std::tuple<std::vector<glm::vec2>, std::vector<glm::vec2>, glm::vec2>(vertices, uvs, dimensions);
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

void HMEngine::UI::Label::InitLabel(bool hasScale)
{
	/* Calculates vertices, uvs, and width and height of the label */
	auto[vertices, uvs, dimensions] = HMEngine::UI::Label::GetVerticesAndUVsFromText(this->_text, this->_font, this->_quadDetails.position, this->_fontSize);

	/* Calculates the width and height of the label */
	if (!hasScale) //if the user didn't specified a scale
	{
		const float ASPECT_RATIO = float(HMEngine::GameSettings::GetWindowWidth()) / HMEngine::GameSettings::GetWindowHeight();
		float width = dimensions.x, height = float(dimensions.y);
		this->SetScale(width, height);
	}

	this->SetVertices(vertices);
	this->SetUVs(uvs);
}
