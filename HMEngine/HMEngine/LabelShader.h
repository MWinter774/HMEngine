#pragma once
#include "Shader.h"

namespace HMEngine
{
	namespace UI
	{
		class Label;
	}

	namespace Core
	{
		class Transform;

		namespace Rendering
		{
			namespace Shaders
			{
				class LabelShader : public HMEngine::Core::Rendering::Shaders::Shader<LabelShader>
				{
					friend class Shader<LabelShader>;
				public:
					void UpdateUniforms(HMEngine::UI::Label& label) override;

				private:
					LabelShader();
					~LabelShader();
					LabelShader(const HMEngine::Core::Rendering::Shaders::LabelShader& other) = delete;
					HMEngine::Core::Rendering::Shaders::LabelShader& operator=(const HMEngine::Core::Rendering::Shaders::LabelShader& other) = delete;
				};
			}
		}
	}
}