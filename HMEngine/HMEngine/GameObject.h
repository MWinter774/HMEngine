#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Components
	{	
		class Component;
		class Draw;
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
		class GameObject
		{
			friend class HMEngine::Components::Component;
		public:
			GameObject();
			~GameObject();
			GameObject(const HMEngine::Core::GameObject& other);
			HMEngine::Core::GameObject& operator=(const HMEngine::Core::GameObject& other);

			inline HMEngine::Core::Transform& GetTransform() const { return *this->_transform; };
			inline std::vector<std::reference_wrapper<HMEngine::Components::Component>> GetComponents() const { return this->_components; }

			void RotateY(float speed);

			void SetTransform(const HMEngine::Core::Transform& transform);

			void Draw() const;

			void AddComponent(HMEngine::Components::Component& component);
		private:
			std::vector<std::reference_wrapper<HMEngine::Components::Component>> _components;
			HMEngine::Core::Transform* _transform;
		};
	}
}
