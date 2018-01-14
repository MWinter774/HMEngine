#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Component.h"
#include "Mesh.h"


namespace HMEngine
{
	namespace Components
	{
		class Texture;

		class MeshRenderer : public Component
		{
		public:
			MeshRenderer(const std::string& meshPath, const std::string& texturePath);
			MeshRenderer(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, const std::vector<glm::vec2>& uvs,const std::string& texturePath);
			virtual ~MeshRenderer();
			MeshRenderer(const HMEngine::Components::MeshRenderer& other);
			HMEngine::Components::MeshRenderer& operator=(const HMEngine::Components::MeshRenderer& other);

			void DrawMesh();

			void AttachToGameObjectEvent() override;
			inline HMEngine::Components::MeshRenderer* Clone() override { return new HMEngine::Components::MeshRenderer(*this); }

			inline HMEngine::Components::Texture& GetTexture() const { return *this->_texture; }

		private:
			enum vboIndexes
			{
				VBO_VERTICES,
				VBO_TEXTURE_COORDS,
				VBO_INDICES,

				NUM_BUFFERS
			};
			std::vector<glm::vec3> _vertices;
			std::vector<GLuint> _indices;
			std::vector<glm::vec2> _uvs;
			std::string _texturePath;
			std::string _meshPath;
			HMEngine::Components::Texture* _texture;
			HMEngine::Core::Mesh* _mesh;

			bool _isAddedToRenderingEngine;


			GLuint _vao;
			GLuint _vbo[NUM_BUFFERS];

			void InitBuffers();
		};
	}
}