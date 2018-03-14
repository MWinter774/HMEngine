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
				class PointLightComponentScreen : public HMEngine::UI::Screen
				{
				public:
					std::function<void(HMEngine::Components::Component*)> _addComponentEvent;

					PointLightComponentScreen(const glm::vec2& centerPos);
					~PointLightComponentScreen();

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

					HMEngine::UI::Label* _lblAttenuationTitle;
					HMEngine::UI::Label* _lblAttenuationX;
					HMEngine::UI::TextBox* _txtAttenuationX;
					HMEngine::UI::Label* _lblAttenuationY;
					HMEngine::UI::TextBox* _txtAttenuationY;
					HMEngine::UI::Label* _lblAttenuationZ;
					HMEngine::UI::TextBox* _txtAttenuationZ;

					HMEngine::UI::Label* _lblRange;
					HMEngine::UI::TextBox* _txtRange;

					HMEngine::UI::Label* _lblIntensityTitle;
					HMEngine::UI::TextBox* _txtIntensity;

					HMEngine::UI::Label* _lblError;
					HMEngine::UI::Button* _btnAddComponent;
				};
			}
		}
	}
}