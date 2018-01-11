#pragma once
#include <iostream>
#include <vector>
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
			GameObject();
			virtual ~GameObject();
			GameObject(const HMEngine::Core::GameObject& other);
			HMEngine::Core::GameObject& operator=(const HMEngine::Core::GameObject& other);

			inline HMEngine::Core::Transform& GetTransform() const { return *this->_transform; };
			inline std::vector<HMEngine::Components::Component*> GetComponents() const { return this->_components; }

			void SetTransform(const HMEngine::Core::Transform& transform);

			void Draw() const;
			void Update() const;

			void AddComponent(HMEngine::Components::Component& component);
		protected:
			std::vector<HMEngine::Components::Component*> _components;
			HMEngine::Core::Transform* _transform;

			void AttachToGameEngine();
		};
	}
}