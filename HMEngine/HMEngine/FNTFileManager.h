#pragma once
#include "FNTFile.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace HMEngine
{
	namespace UI
	{
		class FNTFileManager
		{
		public:
			FNTFileManager() = delete;
			~FNTFileManager() = delete;

			static HMEngine::Core::FNTFile& GetFont(const std::string& fntFilePath);

		private:
			static std::unordered_map<std::string, std::unique_ptr<HMEngine::Core::FNTFile>> fonts; //maps between file path to FNTFile object
		};
	}
}