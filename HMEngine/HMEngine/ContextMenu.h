#pragma once
#include "Quad.h"
#include <string>
#include <vector>
#include "glm\glm.hpp"
#include <functional>

namespace HMEngine
{
	namespace UI
	{
		class Button;

		class ContextMenu : public HMEngine::UI::Quad
		{
		public:
			ContextMenu(const std::string& name, const glm::vec2& position);
			~ContextMenu();
			ContextMenu(const HMEngine::UI::ContextMenu& other);
			HMEngine::UI::ContextMenu& operator=(const HMEngine::UI::ContextMenu& other);

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::ContextMenu(*this); }

			void AddButton(const std::string& buttonName, const std::string& buttonText, const std::function<void()>& onClickEvent);
			void AddButton(const std::string& buttonName, const std::string& buttonText);

		private:
			static const float BUTTON_HEIGHT;

			std::vector<HMEngine::UI::Button*> _buttons;
		};
	}
}