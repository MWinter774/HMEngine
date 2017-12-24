#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class Transform;
		namespace Rendering
		{
			class Camera;
		}
		class GameObject
		{
		public:
			GameObject() {};
			~GameObject() {};
			//bool operator==(const GameObject& go);

			inline std::vector<glm::vec3> GetVertices() { return this->_vertices; };
			inline HMEngine::Core::Transform& GetTransform() { return *this->_transform; };
			inline GLuint GetVao() { return (this->_vao); };
			inline GLuint GetVaoBuffer() { return (this->_vaoBuffer); };

			void SetVertices(std::vector<glm::vec3> vertices);
			inline void SetPos(const HMEngine::Core::Transform& transform);

			//inline void SetPos(const HMEngine::Core::Transform& transform) { *this->_transform = transform; };

			void Draw(GLuint program, glm::mat4 mvp);

		private:
			std::vector<glm::vec3> _vertices;
			std::vector<glm::vec3> _color = {
				glm::vec3(1, 1, 1),
				glm::vec3(0, 1, 1),
				glm::vec3(0, 0, 1),
				glm::vec3(1, 0, 1),
				glm::vec3(1, 0, 0),
				glm::vec3(0, 0, 0),
				glm::vec3(0, 1, 0),
				glm::vec3(1, 1, 0)};
			HMEngine::Core::Transform* _transform;
			GLuint g_Indices[36] = {
				0, 1, 2, 2, 3, 0,           // Front face
				7, 4, 5, 5, 6, 7,           // Back face
				6, 5, 2, 2, 1, 6,           // Left face
				7, 0, 3, 3, 4, 7,           // Right face
				7, 6, 1, 1, 0, 7,           // Top face
				3, 2, 5, 5, 4, 3            // Bottom face
			};
			GLuint _vao = 0;
			GLuint _vaoBuffer = 0;
		};
	}
}
