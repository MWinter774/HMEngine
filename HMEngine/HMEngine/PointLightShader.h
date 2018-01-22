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
				class PointLightShader : public HMEngine::Core::Rendering::Shaders::Shader<PointLightShader>
				{
					friend class Shader<PointLightShader>;
				public:
					void UpdateUniforms(const HMEngine::Core::Transform& transform) override;
					void UpdateUniforms(float shineDamper, float reflectivity) override;
					void UpdateUniforms(const HMEngine::Components::PointLight& pointLight) override;

				private:
					PointLightShader();
					~PointLightShader();
					PointLightShader(const HMEngine::Core::Rendering::Shaders::PointLightShader& other) = delete;
					HMEngine::Core::Rendering::Shaders::PointLightShader& operator=(const HMEngine::Core::Rendering::Shaders::PointLightShader& other) = delete;

					void UpdateTextureUnits();
				};
			}
		}
	}
}