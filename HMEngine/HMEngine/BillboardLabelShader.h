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
				class BillboardLabelShader : public HMEngine::Core::Rendering::Shaders::Shader<BillboardLabelShader>
				{
					friend class Shader<BillboardLabelShader>;
				public:
					void UpdateUniforms(const HMEngine::Core::Transform& transform) override;

				private:
					BillboardLabelShader();
					~BillboardLabelShader();

					HMEngine::Core::Rendering::Camera* _camera;
					glm::mat4& _projectionMatrix;
				};
			}
		}
	}
}