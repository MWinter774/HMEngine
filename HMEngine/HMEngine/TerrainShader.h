#pragma once
#include "Shader.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Rendering
		{
			namespace Shaders
			{
				class TerrainShader : public HMEngine::Core::Rendering::Shaders::Shader<TerrainShader>
				{
					friend class Shader<TerrainShader>;
				public:
					void UpdateUniforms(const HMEngine::Core::Transform& transform) override;
					void UpdateAmbientLight();
					void UpdateFogDensity();
					void UpdateFogGradient();
					void UpdateSkyColor();
					void UpdateTextureUnits();

				private:
					TerrainShader();
					~TerrainShader();
					TerrainShader(const HMEngine::Core::Rendering::Shaders::TerrainShader& other) = delete;
					HMEngine::Core::Rendering::Shaders::TerrainShader& operator=(const HMEngine::Core::Rendering::Shaders::TerrainShader& other) = delete;
				};
			}
		}
	}
}