#pragma once

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
			virtual void UpdateEvent() {} //this functions will be called when the game object is updated
			virtual void AttachToGameObjectEvent() {} //this functions will be called when this component attached to a gameobject

			virtual HMEngine::Components::Component* Clone() = 0; //Return pointer to object

			inline HMEngine::Core::GameObject& GetParent() { return *this->_parentObject; }

		protected:
			HMEngine::Core::GameObject* _parentObject;
		};
	}
}