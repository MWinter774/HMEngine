#pragma once
#include <string>
#include "Player.h"

namespace HMEngine
{
	namespace Core
	{
		namespace WorldEditor
		{
			class WorldEditorPlayerComponent;

			class WorldEditorPlayer : public HMEngine::Player
			{
			public:
				WorldEditorPlayer(const std::string& playerName, float walkingSpeed = 3.0f, float runningSpeed = 10.0f);
				~WorldEditorPlayer();
				WorldEditorPlayer(const HMEngine::Core::WorldEditor::WorldEditorPlayer& other);
				HMEngine::Core::WorldEditor::WorldEditorPlayer& operator=(const HMEngine::Core::WorldEditor::WorldEditorPlayer& other);

			private:
				HMEngine::Core::WorldEditor::WorldEditorPlayerComponent* _worldEditorPlayerComponent;
			};
		}
	}
}