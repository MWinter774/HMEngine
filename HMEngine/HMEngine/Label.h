#pragma once
#include <string>
#include "Quad.h"
#include "Font.h"
#include <tuple>

namespace HMEngine
{
	namespace OpenGL
	{
		class OpenGLQuad;
	}

	namespace UI
	{
		class Label : public HMEngine::UI::Quad
		{
		public:
			Label(const std::string& name, const glm::vec2& position, const std::string& text,
				const HMEngine::UI::Font& font, float fontSize);
			Label(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& text,
				const HMEngine::UI::Font& font, float fontSize);
			~Label();
			Label(const HMEngine::UI::Label& other);
			HMEngine::UI::Label& operator=(const HMEngine::UI::Label& other);

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::Label(*this); }

			inline std::string GetText() const { return this->_text; }
			inline float GetTextSize() const { return this->_fontSize; }
			inline glm::vec3 GetColor() const { return this->_color; }

			void Draw() const override;
			void AttachToGameEngineEvent() override;

		private:
			static std::tuple<std::vector<glm::vec2>, std::vector<glm::vec2>, glm::vec2> GetVerticesAndUVsFromText(const std::string& text, 
				const HMEngine::UI::Font& font, const glm::vec2& bottomLeft, float fontSize);
			static void AddVerticesForCharacter(std::vector<glm::vec2>& vertices, const HMEngine::Core::FNTFile::BMFontCharacter& character, 
				float cursorX, float cursorY, float fontSize);
			static void AddVertices(std::vector<glm::vec2>& vertices, float x, float y, float maxX, float maxY);
			static void AddUVs(std::vector<glm::vec2>& uvs, float x, float y, float maxX, float maxY);

			std::string _text;
			float _fontSize;
			glm::vec3 _color;
			HMEngine::UI::Font _font;
			std::map<GLuint, std::vector<HMEngine::OpenGL::OpenGLQuad*>> _characters; //maps between texture id to vector of OpenGLQuad objects
			GLfloat _width, _height;
		};
	}
}