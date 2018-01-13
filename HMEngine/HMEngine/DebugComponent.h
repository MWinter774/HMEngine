#pragma once
#include "Component.h"

namespace HMEngine
{
	namespace Components
	{
		class DebugComponent : public HMEngine::Components::Component
		{
		public:
			DebugComponent();
			~DebugComponent();

			HMEngine::Components::Component* Clone() override;

			void UpdateEvent() override;
		private:
			int _count = 0;
		};
	}
}