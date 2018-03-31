#pragma once
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <iostream>
#include <vector>
#include "Seb\Seb.h"

namespace HMEngine
{
	namespace Core
	{
		class Mesh
		{
		public:
			Mesh();
			Mesh(const std::string& path);
			Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& normals, const std::vector<GLuint>& indices);
			Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& normals);
			Mesh(const HMEngine::Core::Mesh& other);
			~Mesh();
			void Load(const std::string& path);
			const std::vector<std::string> SplitString(std::string& str);

			HMEngine::Core::Mesh& operator=(HMEngine::Core::Mesh& other);

			inline std::vector<glm::vec3>& GetVertices() { return this->_vertices; };
			inline std::vector<glm::vec3>& GetNormals() { return this->_normals; };
			inline std::vector<glm::vec2>& GetUVs() { return this->_uvs; };
			inline int GetNumIndices() { return this->_numIndices; };
			inline float GetRadius() const { return this->_meshPhysicalData.radius; }
			inline glm::vec3 GetCenter() const { return this->_meshPhysicalData.center; }

			inline void AddVertex(const glm::vec3& vertex) { this->_vertices.push_back(vertex); }
			inline void AddUV(const glm::vec2& uv) { this->_uvs.push_back(uv); }
			inline void AddNormal(const glm::vec3& normal) { this->_normals.push_back(normal); }
			inline void AddIndex(GLuint vertex) { this->_indices.push_back(vertex); }

			void InitBuffers();

			void Draw();

		private:
			static std::pair<glm::vec3, float> GetRadiusAndCenterFromMesh(const std::vector<glm::vec3>& vertices);

			typedef struct
			{
				glm::vec3 center;
				float radius;
			} MeshPhysicalData;

			enum vboIndexes
			{
				VBO_VERTICES,
				VBO_TEXTURE_COORDS,
				VBO_INDICES,
				VBO_NORMALS,

				NUM_BUFFERS
			};

			std::vector<glm::vec3> _vertices;
			std::vector<glm::vec3> _normals;
			std::vector<glm::vec2> _uvs;
			std::vector<GLuint> _indices;

			int _numIndices;

			GLuint _vao;
			GLuint _vbo[NUM_BUFFERS];

			MeshPhysicalData _meshPhysicalData;
		};

	}
}