#pragma once
#include "glm\glm.hpp"
#include "Menu.h"

namespace HMEngine
{
	class GameEngine;

	namespace Core
	{
		namespace WorldEditor
		{
			class AddComponentsScreen : public HMEngine::UI::Menu
			{
			public:
				AddComponentsScreen(const glm::vec2& centerPos);
				~AddComponentsScreen();

				//void Show();
				//void Hide();

				void AddToGameEngine(HMEngine::GameEngine& gameEngine);
				//void BringToFront();

			private:
			};
		}
	}
}