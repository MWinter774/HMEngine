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

					void UpdateTextureUnits();
				};
			}
		}
	}
}