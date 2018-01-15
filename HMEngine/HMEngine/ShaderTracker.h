#pragma once
#include <GL\glew.h>

namespace HMEngine
{
	namespace Core
	{
		namespace Rendering
		{
			namespace Shaders
			{
				class ShaderTracker
				{
				protected:
					static GLuint currentBoundShaderId;
				};
			}
		}
	}
}