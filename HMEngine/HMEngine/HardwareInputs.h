#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	enum class Keys
	{
	};
	namespace Core
	{
		namespace Hardware
		{
			class HardwareInputs
			{
			public:
				void Update();

			private:
				HardwareInputs();
				~HardwareInputs();
			};
		}
	}
}