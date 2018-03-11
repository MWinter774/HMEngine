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
			static HMEngine::UI::Screen* activeScreen;

			Screen(const std::string& screenName, const glm::vec2& centerPos, const glm::vec2& scale);
			virtual ~Screen();
			Screen(const HMEngine::UI::Screen& other);
			HMEngine::UI::Screen& operator=(const HMEngine::UI::Screen& other);

			inline HMEngine::UI::Quad* Clone() const { return new HMEngine::UI::Screen(*this); }

			void SetBackground(const std::string& backgroundTextureFilePath);

			void AddQuad(HMEngine::UI::Quad* quad);

			bool IsFocused() const;

			void MouseButtonDownEvent(const unsigned int& mouseButton) override;

		private:
			HMEngine::UI::QuadCollection* _screen;
			std::vector<HMEngine::UI::Screen*> _subScreens;
		};
	}
}