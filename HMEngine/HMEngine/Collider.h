#pragma once
#include "Component.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			namespace Colliders
			{
				class Collider : public HMEngine::Components::Component
				{
				public:
					Collider();
					virtual ~Collider();

					void AttachToGameObjectEvent() override;

					virtual void Initialize() = 0;
				};
			}
		}
	}
}