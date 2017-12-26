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
				static HMEngine::Core::Rendering::RenderingEngine& GetInstance();

				void Render(const std::vector<HMEngine::Core::GameObject>& gameObjects) const;

			private:
				RenderingEngine();
				~RenderingEngine();
			};
		}
	}
}