#pragma once
#include <string>

namespace HMEngine
{
	namespace OpenGL
	{
		class Texture;
		class UITexture
		{
		public:
			UITexture(const std::string& texturePath);
			~UITexture();
			UITexture(const HMEngine::OpenGL::UITexture& other);
			HMEngine::OpenGL::UITexture& operator=(const HMEngine::OpenGL::UITexture& other);

			void Bind() const;

		private:
			HMEngine::OpenGL::Texture* _texture;
		};
	}
}