#pragma once
#include <string>
#include "Quad.h"
#include "Font.h"

namespace HMEngine
{
	namespace UI
	{
		class Label : public HMEngine::UI::Quad
		{
		public:
			Label(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& text, 
				const HMEngine::UI::Font& font);
			~Label();

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::Label(*this); }

		private:
			std::string _text;
			HMEngine::UI::Font _font;
		};
	}
}