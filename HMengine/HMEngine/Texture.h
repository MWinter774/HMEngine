#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Components
	{
		class Component;

		class Texture : HMEngine::Components::Component
		{
		public:
			Texture(const std::string& texturePath);
			~Texture();
		};
	}
}