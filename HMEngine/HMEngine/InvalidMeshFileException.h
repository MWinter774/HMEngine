#pragma once
#include <exception>
#include <string>

namespace HMEngine
{
	namespace Exceptions
	{
		class InvalidMeshFileException : public std::exception
		{
		public:
			InvalidMeshFileException(const std::string& errorMessage);
			~InvalidMeshFileException();
		};
	}
}