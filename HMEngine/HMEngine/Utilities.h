#pragma once
#include <string>

namespace HMEngine
{
	namespace Core
	{
		class Utilities
		{
		public:
			static void ThrowException(const std::string& errorMessage, const std::string& errorTitle = "Error!");

		private:
			Utilities() = delete;
			~Utilities() = delete;
		};
	}
}