#pragma once
#include "Quad.h"
#include <string>
#include <vector>
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace UI
	{
		class Font;
		class Button;

		class Menu : public HMEngine::UI::Quad
		{
		public:
			Menu(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& backgroundTexturePath);
			~Menu();
			Menu(const HMEngine::UI::Menu& other);
			HMEngine::UI::Menu& operator=(const HMEngine::UI::Menu& other);

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::Menu(*this); }

			void AddButton(const std::string& name, const std::string& buttonReleasedTexture, const std::string& buttonHoverTexture, const std::string& buttonPressedTexture,
				const glm::vec2& position, const glm::vec2& scale, const std::string& labelText, const HMEngine::UI::Font& font, const glm::vec3& labelTextColor,
				float labelFontSize);

		private:
			std::vector<HMEngine::UI::Button*> _buttons;
		};
	}
}