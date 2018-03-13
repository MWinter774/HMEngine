#include "InvalidTextureFileException.h"

HMEngine::Exceptions::InvalidTextureFileException::InvalidTextureFileException(const std::string& errorMessage) : std::exception(errorMessage.c_str())
{
}

HMEngine::Exceptions::InvalidTextureFileException::~InvalidTextureFileException()
{
}