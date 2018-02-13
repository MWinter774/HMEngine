#include "FNTFileManager.h"

std::unordered_map<std::string, std::unique_ptr<HMEngine::Core::FNTFile>> HMEngine::UI::FNTFileManager::fonts;

HMEngine::Core::FNTFile& HMEngine::UI::FNTFileManager::GetFont(const std::string& fntFilePath)
{
	auto& font = HMEngine::UI::FNTFileManager::fonts.find(fntFilePath);
	if (font == HMEngine::UI::FNTFileManager::fonts.end()) //if font file doesnt exist create new one
	{
		HMEngine::UI::FNTFileManager::fonts.insert(std::make_pair(fntFilePath, std::unique_ptr<HMEngine::Core::FNTFile>(new HMEngine::Core::FNTFile(fntFilePath))));
		return *HMEngine::UI::FNTFileManager::fonts[fntFilePath];
	}
	return *(*font).second;
}
