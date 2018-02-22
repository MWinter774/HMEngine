#include "Label.h"
#include "Utilities.h"
#include "OpenGLQuad.h"
#include "GameSettings.h"

HMEngine::UI::Label::Label(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& text,
	const HMEngine::UI::Font& font, float fontSize) : HMEngine::UI::Quad(name, position, scale), _text(text), _font(font), _fontSize(fontSize)
{
	const unsigned int& WINDOW_WIDTH = HMEngine::GameSettings::GetWindowWidth();
	const unsigned int& WINDOW_HEIGHT = HMEngine::GameSettings::GetWindowHeight();
	const float ASPECT_RATIO = float(WINDOW_WIDTH) / WINDOW_HEIGHT;
	this->_width = 0;
	this->_height = 0;
	this->CalculateVerticesAndUVs();
	//this->_width /= ASPECT_RATIO;
	this->_height *= ASPECT_RATIO;
	std::cout << this->_width << std::endl;
	std::cout << this->_height << std::endl;
	this->SetScale(this->_width, scale.y);
}

HMEngine::UI::Label::~Label()
{
	for (auto& item : this->_characters)
		for (auto& quad : item.second)
			delete quad;
}

HMEngine::UI::Label::Label(const HMEngine::UI::Label& other) : HMEngine::UI::Quad(other), _text(other._text), _font(other._font), _fontSize(other._fontSize)
{
	for (auto& item : other._characters)
		for (const auto& quad : item.second)
			this->_characters[item.first].push_back(new HMEngine::OpenGL::OpenGLQuad(*quad));
}

HMEngine::UI::Label& HMEngine::UI::Label::operator=(const HMEngine::UI::Label& other)
{
	if (this != &other)
	{
		HMEngine::UI::Quad::operator=(other);
		this->_text = other._text;
		this->_font = other._font;
		this->_fontSize = other._fontSize;
		for (auto& item : other._characters)
			for (const auto& quad : item.second)
				this->_characters[item.first].push_back(new HMEngine::OpenGL::OpenGLQuad(*quad));
	}

	return *this;
}

void HMEngine::UI::Label::Draw() const
{
	for (auto& item : this->_characters)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, item.first);
		for (auto& quad : item.second)
			quad->Draw(GL_TRIANGLES);
	}
}

void HMEngine::UI::Label::AttachToGameEngineEvent()
{
	for (auto& item : this->_characters)
		for (const auto& quad : item.second)
			quad->Initialize();
}

void HMEngine::UI::Label::CalculateVerticesAndUVs()
{
	this->_characters.clear();
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> uvs;
	GLuint textureId = -1;
	HMEngine::OpenGL::OpenGLQuad* quad = nullptr;
	HMEngine::Core::FNTFile::Glyph glyph;
	GLfloat scale = this->_fontSize;
	GLfloat xPos = -1;
	GLfloat yPos = -1;
	GLfloat w = -1;
	GLfloat h = -1;
	GLfloat x = 0;
	GLfloat y = 0;
	const unsigned int& WINDOW_WIDTH = HMEngine::GameSettings::GetWindowWidth();
	const unsigned int& WINDOW_HEIGHT = HMEngine::GameSettings::GetWindowHeight();
	const float ASPECT_RATIO = float(WINDOW_WIDTH) / WINDOW_HEIGHT;

	for (auto& c : this->_text)
	{
		glyph = this->_font[c];

		textureId = glyph.textureId;
		quad = new HMEngine::OpenGL::OpenGLQuad();

		xPos = x + glyph.offsets.x * scale;
		yPos = y - (glyph.size.y - glyph.offsets.y) * scale;

		w = glyph.size.x * scale;
		h = glyph.size.y * scale;

		// Update VBO for each character
		vertices.push_back(glm::vec2(xPos, yPos + h) /= WINDOW_WIDTH);
		vertices.push_back(glm::vec2(xPos, yPos) /= WINDOW_WIDTH);
		vertices.push_back(glm::vec2(xPos + w, yPos) /= WINDOW_WIDTH);
		vertices.push_back(glm::vec2(xPos, yPos + h) /= WINDOW_WIDTH);
		vertices.push_back(glm::vec2(xPos + w, yPos) /= WINDOW_WIDTH);
		vertices.push_back(glm::vec2(xPos + w, yPos + h) /= WINDOW_WIDTH);

		uvs.push_back(glm::vec2(0.0, 0.0));
		uvs.push_back(glm::vec2(0.0, 1.0));
		uvs.push_back(glm::vec2(1.0, 1.0));
		uvs.push_back(glm::vec2(0.0, 0.0));
		uvs.push_back(glm::vec2(1.0, 1.0));
		uvs.push_back(glm::vec2(1.0, 0.0));

		x += (glyph.advance >> 6) * scale;

		this->_width += (glyph.advance >> 6);/* >> 6) * scale;*/
		this->_height = h > this->_height ? h : this->_height;

		quad->SetVertices(vertices);
		quad->SetUVs(uvs);
		this->_characters[textureId].push_back(quad);

		vertices.clear();
		uvs.clear();
	}
}