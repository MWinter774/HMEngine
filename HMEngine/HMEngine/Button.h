#pragma once
#include "Quad.h"

namespace HMEngine
{
	class GameEngine;
	namespace UI
	{
		class Label;
		class Font;

		class Button : public HMEngine::UI::Quad
		{
		public:
			Button(const std::string& name, const std::string& buttonReleasedTexture, const std::string& buttonHoverTexture, const std::string& buttonPressedTexture,
				const glm::vec2& position, const glm::vec2& scale, const std::string& labelText, const HMEngine::UI::Font& font, const glm::vec3& labelTextColor,
				float labelFontSize);
			~Button();
			Button(const HMEngine::UI::Button& other);
			HMEngine::UI::Button& operator=(const HMEngine::UI::Button& other);

			void UpdateEvent() override;
			void MouseButtonTappedEvent(const unsigned int& mouseButton) override;
			void AttachToGameEngineEvent(HMEngine::GameEngine& gameEngine) override;

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::Button(*this); }

		private:
			typedef unsigned char ButtonState;

			enum
			{
				BUTTON_RELEASED,
				BUTTON_HOVER,
				BUTTON_PRESSED
			};

			std::string _buttonReleasedTexture;
			std::string _buttonPressedTexture;
			HMEngine::UI::Label* _label;
			ButtonState _state;
		};
	}
}