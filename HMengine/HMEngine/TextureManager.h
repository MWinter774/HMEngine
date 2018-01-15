#pragma once
#include "Texture.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace HMEngine
{
	namespace OpenGL
	{
		class TextureManager
		{
		public:
			TextureManager() = delete;
			~TextureManager() = delete;

			static HMEngine::OpenGL::Texture& GetTexture(const std::string& texturePath);

		private:
			static std::unordered_map<std::string, std::unique_ptr<HMEngine::OpenGL::Texture>> textures; //maps between texture file path to texture object
		};
	}
}