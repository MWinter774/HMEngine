#pragma once
//#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class GameObject;
	}

	namespace Components
	{
		class Component
		{
			friend class HMEngine::Core::GameObject;
		public:
			Component();
			virtual ~Component();

			virtual void RenderEvent() {} //this functions will be called when the game object is rendered

		protected:
			HMEngine::Core::GameObject* _parentObject;
		};
	}
}