#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "OpenGLObject.h"

namespace HMEngine
{
	namespace OpenGL
	{
		class OpenGLQuad : public HMEngine::OpenGL::OpenGLObject
		{
		public:
			OpenGLQuad(const std::vector<glm::vec2>& vertices);
			~OpenGLQuad();
			OpenGLQuad(const HMEngine::OpenGL::OpenGLQuad& other);
			HMEngine::OpenGL::OpenGLQuad& operator=(const HMEngine::OpenGL::OpenGLQuad& other);

			void Draw() const;

			inline void SetVertices(const std::vector<glm::vec2>& vertices) { this->_vertices = vertices; }

		private:
			enum
			{
				VBO_VERTICES,

				VBO_COUNT
			};
			GLuint _vao;
			GLuint _vbo[VBO_COUNT];
			std::vector<glm::vec2> _vertices;

			void InitBuffers();
		};
	}
}