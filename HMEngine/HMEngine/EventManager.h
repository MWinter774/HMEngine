#pragma once
#include <set>

namespace HMEngine
{
	namespace Core
	{
		class EventObject;

		class EventManager
		{
		public:
			static void UpdateObjects();
			static void KeyDownEvent(const unsigned int& keyCode);
			static void KeyTappedEvent(const unsigned int& keyCode);
			static void KeyUpEvent(const unsigned int& keyCode);
			static void MouseButtonDownEvent(const unsigned int& keyCode);
			static void MouseButtonTappedEvent(const unsigned int& keyCode);
			static void MouseButtonUpEvent(const unsigned int& keyCode);

			static void RegisterToUpdateEvent(HMEngine::Core::EventObject* object);
			static void RegisterToKeyDownEvent(HMEngine::Core::EventObject* object);
			static void RegisterToKeyTappedEvent(HMEngine::Core::EventObject* object);
			static void RegisterToKeyUpEvent(HMEngine::Core::EventObject* object);
			static void RegisterToMouseButtonDownEvent(HMEngine::Core::EventObject* object);
			static void RegisterToMouseButtonTappedEvent(HMEngine::Core::EventObject* object);
			static void RegisterToMouseButtonUpEvent(HMEngine::Core::EventObject* object);

			static void RemoveObject(HMEngine::Core::EventObject* object);

		private:
			EventManager() = delete;
			~EventManager() = delete;

			static std::set<HMEngine::Core::EventObject*> _updateEventOverriders;
			static std::set<HMEngine::Core::EventObject*> _keyDownEventOverriders;
			static std::set<HMEngine::Core::EventObject*> _keyTappedEventOverriders;
			static std::set<HMEngine::Core::EventObject*> _keyUpEventOverriders;
			static std::set<HMEngine::Core::EventObject*> _mouseButtonDownEventOverriders;
			static std::set<HMEngine::Core::EventObject*> _mouseButtonTappedEventOverriders;
			static std::set<HMEngine::Core::EventObject*> _mouseButtonUpEventOverriders;
		};
	}
}