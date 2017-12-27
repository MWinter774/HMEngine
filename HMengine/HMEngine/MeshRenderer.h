#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Components
	{
		class Component;
		class Texture;

		class MeshRenderer : public Component
		{
		public:
			MeshRenderer(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, const std::vector<glm::vec2>& uvs,const std::string& texturePath);
			virtual ~MeshRenderer();
			MeshRenderer(const HMEngine::Components::MeshRenderer& other);
			HMEngine::Components::MeshRenderer& operator=(const HMEngine::Components::MeshRenderer& other);

			virtual void RenderEvent() override;

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
			HMEngine::Components::Texture* _texture;

			GLuint _vao;
			GLuint _vbo[NUM_BUFFERS];

			void InitBuffers();
		};
	}
}