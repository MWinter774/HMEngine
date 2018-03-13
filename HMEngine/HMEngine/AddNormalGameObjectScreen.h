#pragma once
#include "glm\glm.hpp"
#include "Screen.h"

namespace HMEngine
{
	class GameEngine;
	namespace UI
	{
		class QuadCollection;
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
			class AddComponentsScreen;

			class AddNormalGameObjectScreen : public HMEngine::UI::Screen
			{
			public:
				AddNormalGameObjectScreen(const glm::vec2& centerPos);
				~AddNormalGameObjectScreen();
				AddNormalGameObjectScreen(const HMEngine::Core::WorldEditor::AddNormalGameObjectScreen& other) = delete;
				HMEngine::Core::WorldEditor::AddNormalGameObjectScreen& operator=(const HMEngine::Core::WorldEditor::AddNormalGameObjectScreen& other) = delete;

				void ShowEvent() override;
				
				bool IsChildFocus() const;

			private:
				HMEngine::UI::Button* _btnGameObjectCategory;

				HMEngine::UI::Label* _lblGameObjectName;
				HMEngine::UI::TextBox* _txtGameObjectName;

				HMEngine::UI::Label* _lblGameObjectPositionTitle;
				HMEngine::UI::Label* _lblGameObjectXPosition;
				HMEngine::UI::TextBox* _txtGameObjectXPosition;
				HMEngine::UI::Label* _lblGameObjectYPosition;
				HMEngine::UI::TextBox* _txtGameObjectYPosition;
				HMEngine::UI::Label* _lblGameObjectZPosition;
				HMEngine::UI::TextBox* _txtGameObjectZPosition;

				HMEngine::UI::Label* _lblGameObjectRotationTitle;
				HMEngine::UI::Label* _lblGameObjectXRotation;
				HMEngine::UI::TextBox* _txtGameObjectXRotation;
				HMEngine::UI::Label* _lblGameObjectYRotation;
				HMEngine::UI::TextBox* _txtGameObjectYRotation;
				HMEngine::UI::Label* _lblGameObjectZRotation;
				HMEngine::UI::TextBox* _txtGameObjectZRotation;

				HMEngine::UI::Label* _lblGameObjectScaleTitle;
				HMEngine::UI::Label* _lblGameObjectXScale;
				HMEngine::UI::TextBox* _txtGameObjectXScale;
				HMEngine::UI::Label* _lblGameObjectYScale;
				HMEngine::UI::TextBox* _txtGameObjectYScale;
				HMEngine::UI::Label* _lblGameObjectZScale;
				HMEngine::UI::TextBox* _txtGameObjectZScale;

				HMEngine::UI::Button* _btnAddComponents;

				HMEngine::UI::Button* _btnAddGameObject;

				HMEngine::UI::Label* _lblErrorMsg;
				HMEngine::UI::Label* _lblGameObjectNameErrorMsg;

				HMEngine::Core::WorldEditor::AddComponentsScreen* _addComponentsScreen;

				std::vector<HMEngine::Components::Component*> _gameObjectComponents;

				void ShowNormalGameObjectSettings();
				void HideNormalGameObjectSettings();

				void AddComponent(HMEngine::Components::Component* component);
			};
		}
	}
}