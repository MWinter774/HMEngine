#pragma once
#include <string>
#include <vector>
#include <set>
#include "Component.h"

namespace HMEngine
{
	class GameEngine;
	namespace Core
	{
		class Transform;
		namespace Rendering
		{
			namespace Shaders
			{
				class BasicShader;
			}
		}

		class GameObject
		{
			friend class HMEngine::Components::Component;
			friend class HMEngine::GameEngine;
		public:
			GameObject(const std::string& name);
			virtual ~GameObject();
			GameObject(const HMEngine::Core::GameObject& other);
			HMEngine::Core::GameObject& operator=(const HMEngine::Core::GameObject& other);

			inline HMEngine::Core::Transform& GetTransform() const { return *this->_transform; };
			inline std::vector<HMEngine::Components::Component*> GetComponents() const { return this->_components; }
			inline std::string GetName() const { return this->_name; }
			inline HMEngine::GameEngine& GetGameEngine() { return *this->_gameEngine; }

			void SetTransform(const HMEngine::Core::Transform& transform);

			void Draw() const;
			void Update() const;

			void AddComponent(HMEngine::Components::Component& component);

		protected:
			HMEngine::Core::Transform* _transform;
			HMEngine::GameEngine* _gameEngine;

		private:
			std::vector<HMEngine::Components::Component*> _components;
			std::string _name;

			GameObject(const HMEngine::Core::GameObject& other, bool _1);

			void AttachToGameEngine();
		};
	}
}