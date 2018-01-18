#pragma once
#include "Component.h"
#include <vector>
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class GameObject;
	}
	namespace Components
	{
		class DebugComponent : public HMEngine::Components::Component
		{
		public:
			DebugComponent();
			~DebugComponent();
			DebugComponent(const HMEngine::Components::DebugComponent& other);

			HMEngine::Components::Component* Clone() override;
			void AttachToGameObjectEvent() override;

			void UpdateEvent() override;
		private:
			HMEngine::Core::GameObject* _floor;
			HMEngine::Core::GameObject* _fakeCube;
			std::vector<HMEngine::Core::GameObject*> _crates;
			std::vector<HMEngine::Core::GameObject*> _pointLights;
			std::vector<HMEngine::Core::GameObject*> _monkies;
			std::vector<HMEngine::Core::GameObject*> _pointLightMonkies;
			bool _isAdded;

		};
	}
}