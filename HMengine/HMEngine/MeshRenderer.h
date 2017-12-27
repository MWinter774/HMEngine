#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Components
	{
		class Component;

		class MeshRenderer : public Component
		{
		public:
			MeshRenderer(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices);
			virtual ~MeshRenderer();

			virtual void RenderEvent() override;

		private:
			enum vboIndexes
			{
				VBO_VERTICES,
				VBO_INDICES,

				NUM_BUFFERS
			};
			std::vector<glm::vec3> _vertices;
			std::vector<GLuint> _indices;
			GLuint _vao;
			GLuint _vbo[2];
		};
	}
}