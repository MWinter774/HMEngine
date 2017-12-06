#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class Vertex;

		class GameObject
		{
		public:
			GameObject(HMEngine::Core::Vertex* vertices) {this->_vertices = vertices;};
			~GameObject() {};
			void PlaceGameObject(glm::vec3 pos);
			bool operator==(const GameObject go);

			HMEngine::Core::Vertex* GetVertices() { return this->_vertices; };
			glm::vec3 GetPos() { return this->_pos; };
			void SetVertices(HMEngine::Core::Vertex* vertices) { this->_vertices = vertices; };
			void SetPos(glm::vec3 pos) { this->_pos = pos; };

		private:
			HMEngine::Core::Vertex* _vertices;
			glm::vec3 _pos;

		};
	}
}
