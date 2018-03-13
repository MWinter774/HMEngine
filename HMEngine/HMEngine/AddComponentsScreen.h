#pragma once
#include "glm\glm.hpp"
#include "Screen.h"
#include <functional>

namespace HMEngine
{
	class GameEngine;
	namespace UI
	{
		class Label;
		class TextBox;
		class List;
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
				class MeshRendererComponentScreen;
				class CircleMovementComponentScreen;
			}

			class AddComponentsScreen : public HMEngine::UI::Screen
			{
			public:
				AddComponentsScreen(const glm::vec2& centerPos, const std::function<void(HMEngine::Components::Component*)>& addComponentEvent);
				~AddComponentsScreen();

				void ShowEvent();

				void ComponentAddedEvent(HMEngine::Components::Component* component);

			private:
				HMEngine::UI::Label* _lblAddComponentsTitle;
				HMEngine::UI::TextBox* _txtComponentSearch;
				HMEngine::UI::List* _lstComponentsList;
				std::function<void(HMEngine::Components::Component*)> _addComponentEvent;

				HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen* _scrnMeshRenderer;
				HMEngine::Core::WorldEditor::ComponentScreens::CircleMovementComponentScreen* _scrnCircleMovement;
			};
		}
	}
}