#pragma once
#include "Screen.h"
#include "glm\glm.hpp"
#include <functional>

namespace HMEngine
{
	namespace UI
	{
		class TextBox;
		class Button;
		class Label;
	}
	namespace Components
	{
		class Component;
	}

	namespace Core
	{
		namespace WorldEditor
		{
			namespace ComponentScreens
			{
				class CircleMovementComponentScreen : public HMEngine::UI::Screen
				{
				public:
					std::function<void(HMEngine::Components::Component*)> _addComponentEvent;

					CircleMovementComponentScreen(const glm::vec2& centerPos);
					~CircleMovementComponentScreen();
					
					void ShowEvent() override;

				private:
					HMEngine::UI::Label* _lblTitle;
					HMEngine::UI::Label* _lblCircleCenterTitle;
					HMEngine::UI::Label* _lblXCenter;
					HMEngine::UI::TextBox* _txtXCenter;
					HMEngine::UI::Label* _lblYCenter;
					HMEngine::UI::TextBox* _txtYCenter;
					HMEngine::UI::Label* _lblRadius;
					HMEngine::UI::TextBox* _txtRadius;

					HMEngine::UI::Label* _lblError;
					HMEngine::UI::Button* _btnAddComponent;
				};
			}
		}
	}
}