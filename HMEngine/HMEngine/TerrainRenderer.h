#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>

namespace HMEngine
{
	namespace Components
	{
		class Texture;
		class TerrainRenderer : public HMEngine::Components::Component
		{
		public:
			TerrainRenderer(unsigned int size, const std::string& terrainTexturePath);
			~TerrainRenderer();
			TerrainRenderer(const HMEngine::Components::TerrainRenderer& other);
			HMEngine::Components::TerrainRenderer& operator=(const HMEngine::Components::TerrainRenderer& other);

			void AttachToGameObjectEvent() override;
			HMEngine::Components::Component* Clone() override;

			void DrawTerrain() const;

			inline HMEngine::Components::Texture& GetTexture() { return *this->_texture; }

		private:
			enum vboIndexes
			{
				VBO_VERTICES,
				VBO_TEXTURE_COORDS,
				VBO_INDICES,

				NUM_BUFFERS
			};
			unsigned int _terrainSize;
			unsigned int _vertexCount;
			std::vector<glm::vec3> _vertices;
			std::vector<GLuint> _indices;
			std::vector<glm::vec2> _uvs;
			HMEngine::Components::Texture* _texture;
			bool  _isAddedToRenderingEngine;
			std::string _texturePath;

			GLuint _vao;
			GLuint _vbo[NUM_BUFFERS];

			void GenerateTerrain();
			void InitBuffers();
		};
	}
}