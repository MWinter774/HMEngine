#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class GameObject;

		namespace Rendering
		{
			class RenderingEngine
			{
			public:
				RenderingEngine() = delete;
				~RenderingEngine() = delete;

				static void Render(const std::vector<HMEngine::Core::GameObject>& gameObjects);

			private:
			};
		}
	}
}