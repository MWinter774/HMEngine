#pragma once
#include "Component.h"

namespace HMEngine
{
	namespace UI
	{
		class ContextMenu;
		class Menu;
	}
	namespace Components
	{
		class CameraController;
	}

	namespace Core
	{
		namespace WorldEditor
		{
			class WorldEditorPlayerComponent : public HMEngine::Components::Component
			{
			public:
				WorldEditorPlayerComponent(HMEngine::Components::CameraController& cameraController);
				virtual ~WorldEditorPlayerComponent();
				WorldEditorPlayerComponent(const HMEngine::Core::WorldEditor::WorldEditorPlayerComponent& other);
				HMEngine::Core::WorldEditor::WorldEditorPlayerComponent& operator=(const HMEngine::Core::WorldEditor::WorldEditorPlayerComponent& other);

				inline HMEngine::Components::Component* Clone() { return new HMEngine::Core::WorldEditor::WorldEditorPlayerComponent(*this); }

				void MouseButtonDownEvent(const unsigned int& mouseButton) override;
				void AttachToGameObjectEvent() override;

			private:
				HMEngine::UI::ContextMenu* _menu;
				HMEngine::Components::CameraController* _cameraController;
				HMEngine::UI::Menu* _addGameObjectMenu;
			};
		}
	}
}