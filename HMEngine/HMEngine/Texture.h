#pragma once
#include <string>
#include "OpenGLTexture.h"

namespace HMEngine
{
	namespace OpenGL
	{
		class Texture
		{
			friend class TextureManager;
		public:
			Texture(const std::string& texturePath);
			~Texture();
			Texture(const HMEngine::OpenGL::Texture& other);
			HMEngine::OpenGL::Texture& operator=(const HMEngine::OpenGL::Texture& other);

			void Bind() const;

			inline bool HasTransparency() const { return this->_texture->HasTransparency(); }
			inline std::string GetTexturePath() const { return this->_texture->GetTexturePath(); }
			inline GLuint GetTextureId() const { return this->_texture->GetTextureId(); }
			inline HMEngine::OpenGL::OpenGLTexture& GetOpenGLTexture() { return *this->_texture; }

		private:
			HMEngine::OpenGL::OpenGLTexture* _texture;
		};
	}
}