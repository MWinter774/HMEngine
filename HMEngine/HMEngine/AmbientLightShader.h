#pragma once
#include "Shader.h"

namespace HMEngine::Core
{
	class Transform;
	namespace Rendering::Shaders
	{
		class AmbientLightShader : public HMEngine::Core::Rendering::Shaders::Shader<AmbientLightShader>
		{
			friend class Shader<AmbientLightShader>;
		public:
			void UpdateUniforms(const HMEngine::Core::Transform& transform) override;
			void UpdateAmbientLight();
			void UpdateFogDensity();
			void UpdateFogGradient();
			void UpdateSkyColor();

		private:
			AmbientLightShader();
			~AmbientLightShader();
		};
	}
}