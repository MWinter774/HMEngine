#pragma once
#include "GL\glew.h"
#include "glm\glm.hpp"
#include <vector>
#include <any>
#include <iostream>

namespace HMEngine
{
	namespace OpenGL
	{
		class OpenGLObject
		{
			typedef std::vector<GLuint> GLuintBuffer;
			typedef std::vector<glm::vec2> Vec2Buffer;
			typedef std::vector<glm::vec3> Vec3Buffer;
			typedef std::vector<glm::vec4> Vec4Buffer;
		public:
			OpenGLObject();
			virtual ~OpenGLObject();
			OpenGLObject(const HMEngine::OpenGL::OpenGLObject& other);
			HMEngine::OpenGL::OpenGLObject& operator=(const HMEngine::OpenGL::OpenGLObject& other);

			inline Vec3Buffer Get3dVertices() const { return this->_3dVertices; }
			inline Vec2Buffer Get2dVertices() const { return this->_2dVertices; }
			inline GLuintBuffer GetIndices() const { return this->_indices; }
			inline Vec2Buffer GetUVs() const { return this->_uvs; }
			inline Vec3Buffer GetNormals() const { return this->_normals; }

			inline void SetVertices(const Vec3Buffer& vertices) { this->_3dVertices = vertices; }
			inline void SetVertices(const Vec2Buffer& vertices) { this->_2dVertices = vertices; this->Initialize(); }
			inline void SetIndices(const GLuintBuffer& indices) { this->_indices = indices; this->_hasIndices = indices.size(); }
			inline void SetUVs(const Vec2Buffer& uvs) { this->_uvs = uvs; }
			inline void SetNormals(const Vec3Buffer& normals) { this->_normals = normals; }

			void Initialize();
			void Draw(const unsigned char& drawMode);

		private:
			GLuint _vao;
			std::vector<GLuint> _vbo;
			unsigned int _vboCount;
			bool _isInitialized;
			bool _hasIndices;
			GLuintBuffer _indices;
			Vec2Buffer _uvs;
			unsigned int _uvsIndex;
			Vec2Buffer _2dVertices;
			unsigned int _2dVerticesIndex;
			Vec3Buffer _3dVertices;
			unsigned int _3dVerticesIndex;
			Vec3Buffer _normals;
			unsigned int _normalsIndex;

			void InitVBO();

			void InitBuffers();

			void DeleteBuffers();

			void CalculateVBOCount();
		};
	}
}