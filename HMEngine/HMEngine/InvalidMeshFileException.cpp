#include "InvalidMeshFileException.h"

HMEngine::Exceptions::InvalidMeshFileException::InvalidMeshFileException(const std::string& errorMessage) : std::exception(errorMessage.c_str())
{
}

HMEngine::Exceptions::InvalidMeshFileException::~InvalidMeshFileException()
{
}