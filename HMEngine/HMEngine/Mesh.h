#pragma once
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <iostream>
#include <vector>

namespace HMEngine
{
	namespace Core
	{

		class Mesh
		{
		public:
			Mesh(const std::string& path);
			Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& _normals);
			~Mesh();
			void Load(const std::string& path);
			const std::vector<std::string> SplitString(std::string& str);

			HMEngine::Core::Mesh& operator=(HMEngine::Core::Mesh& other);

			struct fIndices
			{
				int vertexIndex;
				int textureIndex;
				int normalIndex;
			};

			inline std::vector<glm::vec3>& GetVertices() { return this->_vertices; };
			inline std::vector<glm::vec3>& GetNormals() { return this->_normals; };
			inline std::vector<glm::vec2>& GetUVs() { return this->_uvs; };
			inline std::vector<fIndices> GetFaceIndices() { return this->_fIndices; };
			inline int GetNumIndices() { return this->_numIndices; };

			void Draw();

		private:
			enum vboIndexes
			{
				VBO_VERTICES,
				VBO_TEXTURE_COORDS,
				VBO_INDICES,
				VBO_NORMALS,

				NUM_BUFFERS
			};

			std::vector<glm::vec3> _tempVertices;
			std::vector<glm::vec3> _tempNormals;
			std::vector<glm::vec2> _tempUvs;

			std::vector<glm::vec3> _vertices;
			std::vector<glm::vec3> _normals;
			std::vector<glm::vec2> _uvs;

			std::vector<fIndices> _fIndices;

			int _numIndices;

			GLuint _vao;
			GLuint _vbo[NUM_BUFFERS];

			void InitBuffers();

		};

	}
}