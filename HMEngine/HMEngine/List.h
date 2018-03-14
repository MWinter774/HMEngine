#pragma once
#include "Quad.h"
#include <string>
#include <vector>
#include <functional>
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace UI
	{
		class Image;
		class Button;

		class List : public HMEngine::UI::Quad
		{
		public:
			List(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& backgroundTextureFilePath);
			~List();
			List(const HMEngine::UI::List& other);
			HMEngine::UI::List& operator=(const HMEngine::UI::List& other);

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::List(*this); }

			HMEngine::UI::Button* AddButton(const std::string& text, std::function<void(HMEngine::UI::Button*)> onClickEvent);

		private:
			HMEngine::UI::Image* _background;
			std::vector<HMEngine::UI::Button*> _buttons;
		};
	}
}