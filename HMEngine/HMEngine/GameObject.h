#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class Transform;
		class GameObject
		{
		public:
			GameObject() {};
			~GameObject() {};
			//bool operator==(const GameObject& go);

			inline std::vector<glm::vec3> GetVertices() { return this->_vertices; };
			inline HMEngine::Core::Transform& GetTransform() { return *this->_transform; };
			inline void SetVertices(std::vector<glm::vec3> vertices) { this->_vertices = vertices; };
			//inline void SetPos(const HMEngine::Core::Transform& transform) { *this->_transform = transform; };
			void SetPos(const HMEngine::Core::Transform& transform);

		private:
			std::vector<glm::vec3> _vertices;
			HMEngine::Core::Transform* _transform;

		};
	}
}
