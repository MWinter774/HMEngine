#pragma once
#include <GL\glew.h>
#include <string>
#include <lodepng\lodepng.h>

namespace HMEngine
{
	namespace Components
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
				std::size_t operator()(HMEngine::Components::Texture* a) const
				{
					return std::hash<std::string>{}(a->GetTexturePath());
				}
			};
			struct TextureHasher2
			{
				std::size_t operator()(std::reference_wrapper<HMEngine::Components::Texture> a) const
				{
					return std::hash<std::string>{}(a.get().GetTexturePath());
				}
			};
			struct TextureEqualer
			{
				bool operator()(HMEngine::Components::Texture* a, HMEngine::Components::Texture* b) const
				{
					return a->GetTexturePath() == b->GetTexturePath();
				}
			};
			struct TextureEqualer2
			{
				bool operator()(std::reference_wrapper<HMEngine::Components::Texture> a, std::reference_wrapper<HMEngine::Components::Texture> b) const
				{
					return a.get().GetTexturePath() == b.get().GetTexturePath();
				}
			};

			Texture(const std::string& texturePath);
			~Texture();
			Texture(const HMEngine::Components::Texture& other);
			HMEngine::Components::Texture& operator=(const HMEngine::Components::Texture& other);

			void Bind() const;
			inline std::string GetTexturePath() const { return this->_textureImage.imagePath; }

		private:
			GLuint _textureId;
			HMEngine::Components::Texture::Image _textureImage;

			Texture(const std::string& texturePath, bool _1);
		};
	}
}