#pragma once
#include "Quad.h"
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace UI
	{
		class QuadCollection;

		class Screen : public HMEngine::UI::Quad
		{
		public:
			Screen(const std::string& screenName, const glm::vec2& centerPos, const glm::vec2& scale);
			virtual ~Screen();
			Screen(const HMEngine::UI::Screen& other);
			HMEngine::UI::Screen& operator=(const HMEngine::UI::Screen& other);

			inline HMEngine::UI::Quad* Clone() const { return new HMEngine::UI::Screen(*this); }

			//virtual void Show();
			//virtual void Hide();

			void AddQuad(HMEngine::UI::Quad* quad);

			void MouseButtonDownEvent(const unsigned int& mouseButton) override;

		private:
			HMEngine::UI::QuadCollection* _screen;
		};
	}
}