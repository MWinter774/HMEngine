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
			GameObject(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices);
			~GameObject();

			inline std::vector<glm::vec3> GetVertices() { return this->_vertices; };
			inline std::vector<GLuint> GetIndices() { return this->_indices; };
			inline HMEngine::Core::Transform& GetTransform() { return *this->_transform; };
			inline std::vector<HMEngine::Components::Component*> GetComponents() { return this->_components; };

			void SetVertices(std::vector<glm::vec3> vertices) ;
			void SetIndices(std::vector<GLuint> indices);
			void SetTransform(HMEngine::Core::Transform& transform);

			void Draw() const;

			void AddComponent(HMEngine::Components::Component* component);
		private:
			std::vector<glm::vec3> _vertices;
			std::vector<GLuint> _indices;
			std::vector<HMEngine::Components::Component*> _components;


			HMEngine::Core::Transform* _transform;
			GLuint _vao = 0;
			GLuint _vbo[2];
		};
	}
}
