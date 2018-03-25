#pragma once
#include "Quad.h"
#include <string>
#include "glm\glm.hpp"
#include "RenderingEngine.h"

namespace HMEngine
{
	namespace UI
	{
		class Billboard : public HMEngine::UI::Quad
		{
		public:
			Billboard(const std::string& name, const glm::vec3& positionInWorld, const glm::vec2& scale, HMEngine::UI::Quad* quad);
			~Billboard();
			Billboard(const HMEngine::UI::Billboard& other);
			HMEngine::UI::Billboard& operator=(const HMEngine::UI::Billboard& other);

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::Billboard(*this); }

			void AttachToGameEngineEvent() override;

			inline const HMEngine::Core::Rendering::RenderingEngine::Quad& GetQuad() const { return this->_quad; }

		private:
			HMEngine::Core::Rendering::RenderingEngine::Quad _quad;
		};
	}
}