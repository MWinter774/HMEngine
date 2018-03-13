#pragma once
#include <string>
#include <exception>

namespace HMEngine
{
	namespace Exceptions
	{
		class InvalidTextureFileException : public std::exception
		{
		public:
			InvalidTextureFileException(const std::string& errorMessage);
			~InvalidTextureFileException();
		};
	}
}