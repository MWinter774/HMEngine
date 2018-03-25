#pragma once
#include "Shader.h"
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace Core
	{
		class Transform;
		namespace Rendering
		{
			class Camera;

			namespace Shaders
			{
				class BillboardQuadShader : public HMEngine::Core::Rendering::Shaders::Shader<BillboardQuadShader>
				{
					friend class Shader<BillboardQuadShader>;
				public:
					void UpdateUniforms(const HMEngine::Core::Transform& transform) override;

				private:
					BillboardQuadShader();
					~BillboardQuadShader();

					HMEngine::Core::Rendering::Camera* _camera;
					glm::mat4& _projectionMatrix;
				};
			}
		}
	}
}