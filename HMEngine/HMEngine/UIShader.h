#pragma once
#include "Shader.h"

namespace HMEngine
{
	namespace Core
	{
		class Transform;

		namespace Rendering
		{
			namespace Shaders
			{
				class UIShader : public HMEngine::Core::Rendering::Shaders::Shader<UIShader>
				{
					friend class Shader<UIShader>;
				public:
					void UpdateUniforms(const HMEngine::Core::Transform& transform) override;

				private:
					UIShader();
					~UIShader();
					UIShader(const HMEngine::Core::Rendering::Shaders::UIShader& other) = delete;
					HMEngine::Core::Rendering::Shaders::UIShader& operator=(const HMEngine::Core::Rendering::Shaders::UIShader& other) = delete;
				};
			}
		}
	}
}