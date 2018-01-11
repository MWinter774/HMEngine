#include "TextureManager.h"

std::unordered_map<std::string, std::unique_ptr<HMEngine::Components::Texture>> HMEngine::Components::TextureManager::textures;

HMEngine::Components::Texture& HMEngine::Components::TextureManager::GetTexture(const std::string& texturePath)
{
	auto& it = HMEngine::Components::TextureManager::textures.find(texturePath);
	if (it == HMEngine::Components::TextureManager::textures.end()) //if texture doesnt exist create new one
	{
		//HMEngine::Components::TextureManager::textures[texturePath] = std::make_unique<HMEngine::Components::Texture>(new HMEngine::Components::Texture(texturePath, false));
		HMEngine::Components::TextureManager::textures.insert(std::make_pair(texturePath, std::unique_ptr<HMEngine::Components::Texture>(new HMEngine::Components::Texture(texturePath, false))));
		return *HMEngine::Components::TextureManager::textures[texturePath];
	}
	return *(*it).second;
}