#pragma once
#include <GL\glew.h>
#include <string>
#include <lodepng\lodepng.h>

namespace HMEngine
{
	namespace OpenGL
	{
		class Texture
		{
			friend class TextureManager;
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
				std::size_t operator()(HMEngine::OpenGL::Texture* a) const
				{
					return std::hash<std::string>{}(a->GetTexturePath());
				}
			};
			struct TextureHasher2
			{
				std::size_t operator()(std::reference_wrapper<HMEngine::OpenGL::Texture> a) const
				{
					return std::hash<std::string>{}(a.get().GetTexturePath());
				}
			};
			struct TextureEqualer
			{
				bool operator()(HMEngine::OpenGL::Texture* a, HMEngine::OpenGL::Texture* b) const
				{
					return a->GetTexturePath() == b->GetTexturePath();
				}
			};
			struct TextureEqualer2
			{
				bool operator()(std::reference_wrapper<HMEngine::OpenGL::Texture> a, std::reference_wrapper<HMEngine::OpenGL::Texture> b) const
				{
					return a.get().GetTexturePath() == b.get().GetTexturePath();
				}
			};

			Texture(const std::string& texturePath);
			~Texture();
			Texture(const HMEngine::OpenGL::Texture& other);
			HMEngine::OpenGL::Texture& operator=(const HMEngine::OpenGL::Texture& other);

			void Bind() const;
			inline std::string GetTexturePath() const { return this->_textureImage.imagePath; }
			inline bool HasTransparency() const { return this->_hasTransparency; }
			inline GLuint GetTextureId() const { return this->_textureId; }

		private:
			GLuint _textureId;
			HMEngine::OpenGL::Texture::Image _textureImage;
			bool _hasTransparency;

			Texture(const std::string& texturePath, bool _1);
		};
	}
}