#pragma once
#include "Shader.h"
#include "DirectionalLight.h"

namespace HMEngine
{
	namespace Core
	{
		class Transform;

		namespace Rendering
		{
			namespace Shaders
			{
				class BasicShader : public HMEngine::Core::Rendering::Shaders::Shader<BasicShader>
				{
					friend class Shader<BasicShader>;
				public:
					void UpdateUniforms(const HMEngine::Core::Transform& transform) override;
					void UpdateAmbientLight();
					void UpdateFogDensity();
					void UpdateFogGradient();
					void UpdateSkyColor();

				private:
					BasicShader();
					~BasicShader();
					BasicShader(const HMEngine::Core::Rendering::Shaders::BasicShader& other) = delete;
					HMEngine::Core::Rendering::Shaders::BasicShader& operator=(const HMEngine::Core::Rendering::Shaders::BasicShader& other) = delete;
				};
			}
		}
	}
}