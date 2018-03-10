#pragma once
#include "glm\glm.hpp"
#include "Screen.h"

namespace HMEngine
{
	class GameEngine;
	namespace UI
	{
		class Label;
	}

	namespace Core
	{
		namespace WorldEditor
		{
			class AddComponentsScreen : public HMEngine::UI::Screen
			{
			public:
				AddComponentsScreen(const glm::vec2& centerPos);
				~AddComponentsScreen();

			private:
				HMEngine::UI::Label* _lblAddComponentsTitle;
			};
		}
	}
}