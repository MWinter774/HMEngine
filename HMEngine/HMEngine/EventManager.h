#pragma once
#include <set>

namespace HMEngine
{
	namespace Core
	{
		class GameEngineObject;

		class EventManager
		{
		public:
			static void UpdateObjects();

			static void AddUpdateEventOverrider(HMEngine::Core::GameEngineObject* object);
			static void AddDrawEventOverrider(HMEngine::Core::GameEngineObject* object);

		private:
			EventManager() = delete;
			~EventManager() = delete;

			static std::set<HMEngine::Core::GameEngineObject*> _updateOverriders;
			static std::set<HMEngine::Core::GameEngineObject*> _drawOverriders;
		};
	}
}