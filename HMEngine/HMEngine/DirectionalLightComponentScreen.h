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
				class DirectionalLightComponentScreen : public HMEngine::UI::Screen
				{
				public:
					std::function<void(HMEngine::Components::Component*)> _addComponentEvent;

					DirectionalLightComponentScreen(const glm::vec2& centerPos);
					~DirectionalLightComponentScreen();

					void ShowEvent() override;

				private:
					HMEngine::UI::Label* _lblTitle;

					HMEngine::UI::Label* _lblColorTitle;
					HMEngine::UI::Label* _lblColorR;
					HMEngine::UI::TextBox* _txtColorR;
					HMEngine::UI::Label* _lblColorG;
					HMEngine::UI::TextBox* _txtColorG;
					HMEngine::UI::Label* _lblColorB;
					HMEngine::UI::TextBox* _txtColorB;

					HMEngine::UI::Label* _lblIntensityTitle;
					HMEngine::UI::TextBox* _txtIntensity;

					HMEngine::UI::Label* _lblDirectionTitle;
					HMEngine::UI::Label* _lblDirectionX;
					HMEngine::UI::TextBox* _txtDirectionX;
					HMEngine::UI::Label* _lblDirectionY;
					HMEngine::UI::TextBox* _txtDirectionY;
					HMEngine::UI::Label* _lblDirectionZ;
					HMEngine::UI::TextBox* _txtDirectionZ;

					HMEngine::UI::Label* _lblError;
					HMEngine::UI::Button* _btnAddComponent;
				};
			}
		}
	}
}