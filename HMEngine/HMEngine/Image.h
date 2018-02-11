#pragma once
#include "Quad.h"
#include "glm\glm.hpp"
#include <string>
#include <vector>

namespace HMEngine
{
	namespace OpenGL
	{
		class UITexture;
	}
	namespace UI
	{
		class Image : public HMEngine::UI::Quad
		{
		public:
			Image(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale);
			~Image();

			void Update() override;

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::Image(*this); }
		};
	}
}