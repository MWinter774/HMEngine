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
			static void PrintDebugMessage(const std::string& message, const std::string& messageType = "DEBUG", unsigned char foregroundColor = 7, unsigned char backgroundColor = 0);

		private:
			Utilities() = delete;
			~Utilities() = delete;
		};
	}
}