#pragma once
#include "Quad.h"

namespace HMEngine
{
	class GameEngine;
	namespace UI
	{
		class Label;
		class Font;

		class TextBox : public HMEngine::UI::Quad
		{
		public:
			TextBox(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const HMEngine::UI::Font& font, bool acceptLetters = true);
			~TextBox();
			TextBox(const HMEngine::UI::TextBox& other);
			HMEngine::UI::TextBox& operator=(const HMEngine::UI::TextBox& other);

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::TextBox(*this); }

			void KeyDownEvent(const unsigned int& keyCode) override;
			void MouseButtonDownEvent(const unsigned int& mouseButtonCode) override;

			void SetText(const std::string& text);

			std::string GetText() const;
			bool IsEmpty() const;

		private:
			bool _isFocused;
			HMEngine::UI::Label* _label;
			bool _acceptLetters;
		};
	}
}