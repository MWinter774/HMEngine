#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class Transform;

		namespace Rendering
		{
			namespace Shaders
			{
				template<typename T>
				class Shader;

				class BasicShader : public HMEngine::Core::Rendering::Shaders::Shader<BasicShader>
				{
					friend class Shader<BasicShader>;
				public:
					void UpdateUniforms(const HMEngine::Core::Transform& transform) override;

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