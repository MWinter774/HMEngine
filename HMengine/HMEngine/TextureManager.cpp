#include "TextureManager.h"

std::unordered_map<std::string, std::unique_ptr<HMEngine::OpenGL::Texture>> HMEngine::OpenGL::TextureManager::textures;

HMEngine::OpenGL::Texture& HMEngine::OpenGL::TextureManager::GetTexture(const std::string& texturePath)
{
	auto& it = HMEngine::OpenGL::TextureManager::textures.find(texturePath);
	if (it == HMEngine::OpenGL::TextureManager::textures.end()) //if texture doesnt exist create new one
	{
		//HMEngine::Components::TextureManager::textures[texturePath] = std::make_unique<HMEngine::Components::Texture>(new HMEngine::Components::Texture(texturePath, false));
		HMEngine::OpenGL::TextureManager::textures.insert(std::make_pair(texturePath, std::unique_ptr<HMEngine::OpenGL::Texture>(new HMEngine::OpenGL::Texture(texturePath, false))));
		return *HMEngine::OpenGL::TextureManager::textures[texturePath];
	}
	return *(*it).second;
}