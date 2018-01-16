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
				class DirectionalLightShader : public HMEngine::Core::Rendering::Shaders::Shader<DirectionalLightShader>
				{
					friend class Shader<DirectionalLightShader>;
				public:
					void UpdateUniforms(const HMEngine::Core::Transform& transform) override;
					void UpdateUniforms(const HMEngine::Components::DirectionalLight& directionalLight) override;

				private:
					DirectionalLightShader();
					~DirectionalLightShader();
					DirectionalLightShader(const HMEngine::Core::Rendering::Shaders::DirectionalLightShader& other) = delete;
					HMEngine::Core::Rendering::Shaders::DirectionalLightShader& operator=(const HMEngine::Core::Rendering::Shaders::DirectionalLightShader& other) = delete;
				};
			}
		}
	}
}