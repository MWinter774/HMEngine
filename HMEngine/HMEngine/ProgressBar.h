#pragma once
#include "Quad.h"
#include <string>
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace UI
	{
		class Image;

		class ProgressBar : public HMEngine::UI::Quad
		{
		public:
			ProgressBar(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& backgroundTexturePath,
				const std::string& barTexturePath, float percentage = 0, bool is3D = false);
			~ProgressBar();

			inline HMEngine::UI::Quad* Clone() const override { return new HMEngine::UI::ProgressBar(*this); }

			void SetPercentage(float percentage);
			inline float GetPercentage() const { return this->_percentage; }
			inline void DecreaseBar(float percentageAmount) { this->SetPercentage(this->_percentage - percentageAmount); }
			inline void IncreaseBar(float percentageAmount) { this->SetPercentage(this->_percentage + percentageAmount); }

		private:
			HMEngine::UI::Image* _background;
			HMEngine::UI::Image* _bar;
			float _percentage;
			bool _is3D;
		};
	}
}