#pragma once
#include "Quad.h"
#include "glm\glm.hpp"
#include <string>
#include <vector>

namespace HMEngine
{
	namespace UI
	{
		class QuadCollection : public HMEngine::UI::Quad
		{
		public:
			QuadCollection(const std::string& name, const glm::vec2& position, const glm::vec2& scale);
			~QuadCollection();
			QuadCollection(const HMEngine::UI::QuadCollection& other);
			HMEngine::UI::QuadCollection& operator=(const HMEngine::UI::QuadCollection& other);

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::QuadCollection(*this); }

			void AddQuad(const HMEngine::UI::Quad& quadToAdd);
			void AddQuad(HMEngine::UI::Quad* quadToAdd);

			private:
				std::vector<HMEngine::UI::Quad*> _quads;
		};
	}
}