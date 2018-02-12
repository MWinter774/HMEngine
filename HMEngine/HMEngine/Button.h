#pragma once
#include "Quad.h"

namespace HMEngine
{
	namespace UI
	{
		class Button : public HMEngine::UI::Quad
		{
		public:
			Button(const std::string& name, const std::string& buttonReleasedTexture, const std::string& buttonHoverTexture, const std::string& buttonPressedTexture, const glm::vec2& position, const glm::vec2& scale);
			~Button();

			void Update() override;

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::Button(*this); }

		private:
			enum
			{
				BUTTON_RELEASED,
				BUTTON_HOVER,
				BUTTON_PRESSED
			};

			std::string _buttonReleasedTexture;
			std::string _buttonPressedTexture;
		};
	}
}