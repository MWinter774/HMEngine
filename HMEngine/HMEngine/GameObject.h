#pragma once
#include <string>
#include <vector>
#include <set>
#include "Component.h"
#include "glm\glm.hpp"

namespace HMEngine
{
	class GameEngine;

	namespace Components
	{
		class MeshRenderer;
	}
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
		namespace Physics
		{
			namespace Colliders
			{
				class Collider;
			}
		}

		class GameObjectCore
		{
		public:
			virtual HMEngine::Core::GameObject* Clone() const = 0;
		};

		class GameObject : public GameObjectCore
		{
			friend class HMEngine::Components::Component;
			friend class HMEngine::GameEngine;
		public:
			GameObject(const std::string& name);
			virtual ~GameObject();
			GameObject(const HMEngine::Core::GameObject& other);
			HMEngine::Core::GameObject& operator=(const HMEngine::Core::GameObject& other);

			virtual HMEngine::Core::GameObject* Clone() const override { return new HMEngine::Core::GameObject(*this); }

			inline HMEngine::Core::Transform& GetTransform() const { return *this->_transform; };
			inline std::vector<HMEngine::Components::Component*> GetComponents() const { return this->_components; }
			inline std::string GetName() const { return this->_name; }
			inline HMEngine::GameEngine& GetGameEngine() { return *this->_gameEngine; }

			void SetTransform(const HMEngine::Core::Transform& transform);

			void AddComponent(HMEngine::Components::Component& component);
			void AddComponent(HMEngine::Components::Component* component);

			inline virtual void AttachToGameEngineEvent() {}

			inline HMEngine::Components::MeshRenderer* GetMeshRenderer() const { return this->_meshRenderer; }

			void Move(const glm::vec3& direction, float amount);
			inline void AddPositionX(float x) { this->Move(glm::vec3(1, 0, 0), x); }
			inline void AddPositionY(float y) { this->Move(glm::vec3(0, 1, 0), y); }
			inline void AddPositionZ(float z) { this->Move(glm::vec3(0, 0, 1), z); }
			inline void AddPosition(const glm::vec3& other) { this->Move(other, 1); }
			inline void AddPosition(float x, float y, float z) { this->Move(glm::vec3(x, y, z), 1); }
			inline void AddPosition(float count) { this->Move(glm::vec3(1, 1, 1), count); }

		protected:
			HMEngine::Core::Transform* _transform;
			HMEngine::GameEngine* _gameEngine;

			void AttachToGameEngine();

		private:
			std::vector<HMEngine::Components::Component*> _components;
			std::string _name;
			HMEngine::Components::MeshRenderer* _meshRenderer;
			HMEngine::Core::Physics::Colliders::Collider* _collider;

			GameObject(const HMEngine::Core::GameObject& other, bool _1);
		};
	}
}