#pragma once
#include "glm\glm.hpp"
#include "Screen.h"

namespace HMEngine
{
	class GameEngine;
	namespace UI
	{
		class Label;
		class TextBox;
		class List;
	}

	namespace Core
	{
		namespace WorldEditor
		{
			namespace ComponentScreens
			{
				class MeshRendererComponentScreen;
			}

			class AddComponentsScreen : public HMEngine::UI::Screen
			{
			public:
				AddComponentsScreen(const glm::vec2& centerPos);
				~AddComponentsScreen();

				void ShowEvent();

			private:
				HMEngine::UI::Label* _lblAddComponentsTitle;
				HMEngine::UI::TextBox* _txtComponentSearch;
				HMEngine::UI::List* _lstComponentsList;

				HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen* _meshRendererScreen;
			};
		}
	}
}