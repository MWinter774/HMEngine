#pragma once

namespace HMEngine
{
	class GameEngine;

	namespace Core
	{
		namespace WorldEditor
		{
			class WorldEditorPlayer;
			class WorldEditor
			{
			public:
				WorldEditor(HMEngine::GameEngine& gameEngine);
				~WorldEditor();
				WorldEditor(const HMEngine::Core::WorldEditor::WorldEditor& other);
				HMEngine::Core::WorldEditor::WorldEditor& operator=(const HMEngine::Core::WorldEditor::WorldEditor& other);

				void Initialize();
			private:
				HMEngine::GameEngine* _gameEngine;
				HMEngine::Core::WorldEditor::WorldEditorPlayer* _player;
			};
		}
	}
}