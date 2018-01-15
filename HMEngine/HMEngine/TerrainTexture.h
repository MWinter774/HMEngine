#pragma once
#include <string>

namespace HMEngine
{
	namespace OpenGL
	{
		class Texture;
		class TerrainTexture
		{
		public:
			TerrainTexture(const std::string& backroundTextureFilePath, const std::string& rTextureFilePath, const std::string& gTextureFilePath, const std::string& bTextureFilePath, const std::string& blendMapFilePath);
			~TerrainTexture();
			TerrainTexture(const HMEngine::OpenGL::TerrainTexture& other);
			HMEngine::OpenGL::TerrainTexture& operator=(const HMEngine::OpenGL::TerrainTexture& other);

			void Bind() const;

		private:
			HMEngine::OpenGL::Texture* _backgroundTexture;
			HMEngine::OpenGL::Texture* _rTexture;
			HMEngine::OpenGL::Texture* _gTexture;
			HMEngine::OpenGL::Texture* _bTexture;
			HMEngine::OpenGL::Texture* _blendMap;
		};
	}
}