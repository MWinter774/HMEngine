#pragma once
#include <string>
#include <vector>
#include "GL\glew.h"

namespace HMEngine
{
	namespace OpenGL
	{
		class OpenGLTexture
		{
			typedef struct Image
			{
				std::string imagePath;
				unsigned int width;
				unsigned int height;
				std::vector<unsigned char> image;
			} Image;
		public:
			struct TextureHasher
			{
				std::size_t operator()(HMEngine::OpenGL::OpenGLTexture* a) const
				{
					return std::hash<std::string>{}(a->_textureImage.imagePath);
				}
			};
			struct TextureHasher2
			{
				std::size_t operator()(std::reference_wrapper<HMEngine::OpenGL::OpenGLTexture> a) const
				{
					return std::hash<std::string>{}(a.get()._textureImage.imagePath);
				}
			};
			struct TextureEqualer
			{
				bool operator()(HMEngine::OpenGL::OpenGLTexture* a, HMEngine::OpenGL::OpenGLTexture* b) const
				{
					return a->_textureImage.imagePath == b->_textureImage.imagePath;
				}
			};
			struct TextureEqualer2
			{
				bool operator()(std::reference_wrapper<HMEngine::OpenGL::OpenGLTexture> a, std::reference_wrapper<HMEngine::OpenGL::OpenGLTexture> b) const
				{
					return a.get()._textureImage.imagePath == b.get()._textureImage.imagePath;
				}
			};
			OpenGLTexture(const std::string& texturePath, const unsigned int& internalFormat);
			~OpenGLTexture();

			void Bind() const;

			inline std::string GetTexturePath() const { return this->_textureImage.imagePath; }
			inline GLuint GetTextureId() const { return this->_textureId; }
			inline bool HasTransparency() const { return this->_hasTransparency; }

		private:
			bool _hasTransparency;
			GLuint _textureId;
			HMEngine::OpenGL::OpenGLTexture::Image _textureImage;
		};
	}
}