#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Components
	{
		class Texture
		{
			typedef struct Image
			{
				unsigned int width;
				unsigned int height;
				//unsigned char* image;
				std::vector<unsigned char> image;
			} Image;
		public:
			Texture(const std::string& texturePath);
			~Texture();
			Texture(const HMEngine::Components::Texture& other);
			HMEngine::Components::Texture& operator=(const HMEngine::Components::Texture& other);

			void Bind() const;

		private:
			GLuint _textureId;
			HMEngine::Components::Texture::Image _textureImage;

		};
	}
}