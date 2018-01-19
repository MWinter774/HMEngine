#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "opencv2\opencv.hpp"

namespace HMEngine
{
	namespace OpenGL
	{
		class Texture;
		class TerrainTexture;
	}
	namespace Components
	{
		class TerrainRenderer : public HMEngine::Components::Component
		{
		public:
			TerrainRenderer(unsigned int size, const std::string& backroundTextureFilePath, const std::string& rTextureFilePath, const std::string& gTextureFilePath, const std::string& bTextureFilePath, const std::string& blendMapFilePath);
			TerrainRenderer(unsigned int size, const std::string& backroundTextureFilePath);
			TerrainRenderer(unsigned int size, float maxHeight, const std::string& heightMapPath, const std::string& texturePath);
			TerrainRenderer(unsigned int size, float maxHeight, const std::string& heightMapPath, const std::string& backroundTextureFilePath, const std::string& rTextureFilePath, const std::string& gTextureFilePath, const std::string& bTextureFilePath, const std::string& blendMapFilePath);
			~TerrainRenderer();
			TerrainRenderer(const HMEngine::Components::TerrainRenderer& other);
			HMEngine::Components::TerrainRenderer& operator=(const HMEngine::Components::TerrainRenderer& other);

			void AttachToGameObjectEvent() override;
			inline HMEngine::Components::Component* Clone() override { return new HMEngine::Components::TerrainRenderer(*this); }

			void BindTextures() const;
			void DrawTerrain() const;

			inline HMEngine::OpenGL::Texture& GetTexture() { return *this->_texture; }

		private:
			static constexpr float MAX_PIXEL_COLOR = 256 * 256 * 256;

			enum vboIndexes
			{
				VBO_VERTICES,
				VBO_TEXTURE_COORDS,
				VBO_INDICES,

				NUM_BUFFERS
			};
			unsigned int _terrainSize;
			unsigned int _vertexCount;
			unsigned int _maxHeight;
			std::vector<glm::vec3> _vertices;
			std::vector<GLuint> _indices;
			std::vector<glm::vec2> _uvs;
			HMEngine::OpenGL::Texture* _texture;
			HMEngine::OpenGL::TerrainTexture* _terrainTexture;
			bool  _isAddedToRenderingEngine;
			std::string _backroundTexturePath;
			std::string _rTexturePath;
			std::string _gTexturePath;
			std::string _bTexturePath;
			std::string _blendMapTexturePath;

			GLuint _vao;
			GLuint _vbo[NUM_BUFFERS];

			void GenerateTerrain();
			void GenerateTerrain(const std::string& heightMapPath);
			void InitBuffers();
			float GetHeightFromPixel(const cv::Mat& image, unsigned int x, unsigned int y);
			glm::vec3 CalculateNormal(const cv::Mat& image, unsigned int x, unsigned int y);
		};
	}
}