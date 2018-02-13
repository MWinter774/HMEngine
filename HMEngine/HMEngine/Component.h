#pragma once
#include <string>
#include <vector>

namespace HMEngine
{
	namespace Core
	{
		class GameObject;
	}
	namespace UI
	{
		class Quad;
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

			virtual HMEngine::Components::Component* Clone() = 0; //returns pointer to object

			inline HMEngine::Core::GameObject& GetParent() { return *this->_parentObject; }

		protected:
			HMEngine::Core::GameObject* _parentObject;
			bool _isAttachedToGameObject;

			std::vector<HMEngine::Core::GameObject*> GetGameObjects() const;
			HMEngine::Core::GameObject* GetGameObject(const std::string& name) const;

			void AddGameObject(const HMEngine::Core::GameObject& go) const;
			void AddGameObject(HMEngine::Core::GameObject* go) const;
			void RemoveGameObject(const std::string& name) const;
			void AddUI(const HMEngine::UI::Quad& ui) const;
			void AddUI(HMEngine::UI::Quad* ui) const;
			void RemoveUI(const std::string& name) const;

		private:
			void AttachToGameObject();
		};
	}
}