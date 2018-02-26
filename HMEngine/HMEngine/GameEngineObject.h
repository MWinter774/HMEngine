#pragma once
#include <iostream>
#include <any>
#include "EventManager.h"

namespace HMEngine
{
	class GameEngine;

	namespace Core
	{
		class GameEngineObject
		{
		public:
			GameEngineObject();
			virtual ~GameEngineObject();

			inline virtual void UpdateEvent() {}
			inline virtual void DrawEvent() {}
			inline virtual void AttachToGameEngineEvent(HMEngine::GameEngine& gameEngine) {}
			inline virtual void KeyDownEvent(unsigned int keyCode) {}
			inline virtual void KeyTappedEvent(unsigned int keyCode) {}
			inline virtual void KeyUpEvent(unsigned int keyCode) {}

			template <class Derived>
			void InitializeEvents(Derived* const derived)
			{
				this->_object = derived;
				/* Checks if derived class overrided functions */
				if (!std::is_same<decltype(&GameEngineObject::UpdateEvent), decltype(&Derived::UpdateEvent)>::value)
				{
					this->_hasUpdateEvent = true;
				}
				if (!std::is_same<decltype(&GameEngineObject::DrawEvent), decltype(&Derived::DrawEvent)>::value)
				{
					this->_hasDrawEvent = true;
				}
			}

			void InitializeGameEngineObject();

		protected:
			bool _isAttachedToGameEngine;
			HMEngine::GameEngine* _gameEngine;
			HMEngine::Core::GameEngineObject* _object; //the object that inherits from this class(e.g. Label, Button, Terrain...)
			bool _hasUpdateEvent;
			bool _hasDrawEvent;

		private:
			virtual void AttachToGameEngine(HMEngine::GameEngine& gameEngine);
		};
	}
}