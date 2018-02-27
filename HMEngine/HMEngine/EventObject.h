#pragma once
#include <iostream>
#include <any>
#include "EventManager.h"

namespace HMEngine
{
	class GameEngine;

	namespace Core
	{
		class EventObject
		{
		public:
			EventObject();
			virtual ~EventObject();

			inline virtual void UpdateEvent() {} //handled by the event manager
			inline virtual void AttachToGameEngineEvent(HMEngine::GameEngine& gameEngine) {} //handled by the game object
			inline virtual void KeyDownEvent(const unsigned int& keyCode) {} //handled by the event manager
			inline virtual void KeyTappedEvent(const unsigned int& keyCode) {} //handled by the event manager
			inline virtual void KeyUpEvent(const unsigned int& keyCode) {} //handled by the event manager
			inline virtual void MouseButtonDownEvent(const unsigned int& mouseButtonCode) {} //handled by the event manager
			inline virtual void MouseButtonTappedEvent(const unsigned int& mouseButtonCode) {} //handled by the event manager
			inline virtual void MouseButtonUpEvent(const unsigned int& mouseButtonCode) {} //handled by the event manager

			template <class Derived>
			void InitializeEvents(Derived* const derived)
			{
				this->_object = derived;
				/* Checks if derived class overrided functions */
				if (!std::is_same<decltype(&EventObject::UpdateEvent), decltype(&Derived::UpdateEvent)>::value)
				{
					this->_hasUpdateEvent = true;
				}
				if (!std::is_same<decltype(&EventObject::KeyDownEvent), decltype(&Derived::KeyDownEvent)>::value)
				{
					this->_hasKeyDownEvent = true;
				}
				if (!std::is_same<decltype(&EventObject::KeyTappedEvent), decltype(&Derived::KeyTappedEvent)>::value)
				{
					this->_hasKeyTappedEvent = true;
				}
				if (!std::is_same<decltype(&EventObject::KeyUpEvent), decltype(&Derived::KeyUpEvent)>::value)
				{
					this->_hasKeyUpEvent = true;
				}
				if (!std::is_same<decltype(&EventObject::MouseButtonDownEvent), decltype(&Derived::MouseButtonDownEvent)>::value)
				{
					this->_hasMouseButtonDownEvent = true;
				}
				if (!std::is_same<decltype(&EventObject::MouseButtonTappedEvent), decltype(&Derived::MouseButtonTappedEvent)>::value)
				{
					this->_hasMouseButtonTappedEvent = true;
				}
				if (!std::is_same<decltype(&EventObject::MouseButtonUpEvent), decltype(&Derived::MouseButtonUpEvent)>::value)
				{
					this->_hasMouseButtonUpEvent = true;
				}
			}

			void InitializeEventObject();

		protected:
			HMEngine::Core::EventObject* _object; //the object that inherits from this class(e.g. Label, Button, Terrain...)
			bool _hasUpdateEvent;
			bool _hasKeyDownEvent;
			bool _hasKeyTappedEvent;
			bool _hasKeyUpEvent;
			bool _hasMouseButtonDownEvent;
			bool _hasMouseButtonTappedEvent;
			bool _hasMouseButtonUpEvent;
		};
	}
}