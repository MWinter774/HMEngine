#pragma once
#include <GL\glew.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Texture.h"

namespace HMEngine
{
	namespace Components
	{
		class Texture;
		class MeshRenderer;
	}
	namespace Core
	{
		class GameObject;

		namespace Rendering
		{
			class RenderingEngine
			{
			public:
				static HMEngine::Core::Rendering::RenderingEngine& GetInstance();

				void Render(const std::vector<HMEngine::Core::GameObject*>& gameObjects) const;

				void AddMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer);
				void RemoveMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer);

			private:
				RenderingEngine();
				~RenderingEngine();
				RenderingEngine(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;
				HMEngine::Core::Rendering::RenderingEngine& operator=(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;

				//std::unordered_map<std::reference_wrapper<HMEngine::Components::Texture>, std::vector<std::reference_wrapper<HMEngine::Components::MeshRenderer>>, HMEngine::Components::Texture::TextureHasher, HMEngine::Components::Texture::TextureEqualer> _textures;
				std::unordered_map<HMEngine::Components::Texture*, std::vector<HMEngine::Components::MeshRenderer*>, HMEngine::Components::Texture::TextureHasher, HMEngine::Components::Texture::TextureEqualer> _textures;
			};
		}
	}
}