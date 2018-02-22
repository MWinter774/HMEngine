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
			OpenGLQuad();
			OpenGLQuad(const std::vector<glm::vec2>& vertices);
			OpenGLQuad(const std::vector<glm::vec2>& vertices, const std::vector<glm::vec2>& uvs);
			~OpenGLQuad();

		private:
		};
	}
}