#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
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
		public:
			GameObject(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices);
			~GameObject() {};

			inline std::vector<glm::vec3> GetVertices() { return this->_vertices; };
			inline std::vector<GLuint> GetIndices() { return this->_indices; };
			inline HMEngine::Core::Transform& GetTransform() { return *this->_transform; };

			void SetVertices(std::vector<glm::vec3> vertices) ;
			void SetIndices(std::vector<GLuint> indices);
			void SetTransform(HMEngine::Core::Transform& transform);
			void Draw();


		private:
			std::vector<glm::vec3> _vertices;
			std::vector<GLuint> _indices;

			HMEngine::Core::Transform* _transform;
			GLuint _vao = 0;
			GLuint _vbo[2];
		};
	}
}
