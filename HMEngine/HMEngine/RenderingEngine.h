#pragma once
#include <GL\glew.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Texture.h"
#include "DirectionalLight.h"
#include <unordered_set>

namespace HMEngine
{
	namespace Components
	{
		class Texture;
		class MeshRenderer;
		class DirectionalLight;
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

				void Render() const;

				void AddMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer);
				void RemoveMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer);
				void HMEngine::Core::Rendering::RenderingEngine::AddDirectionalLight(HMEngine::Components::DirectionalLight& directionalLight);


			private:
				RenderingEngine();
				~RenderingEngine();
				RenderingEngine(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;
				HMEngine::Core::Rendering::RenderingEngine& operator=(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;

				std::unordered_map<HMEngine::Components::Texture*, std::vector<HMEngine::Components::MeshRenderer*>, HMEngine::Components::Texture::TextureHasher, HMEngine::Components::Texture::TextureEqualer> _textures;

				std::unordered_set<HMEngine::Components::DirectionalLight*> _directionalLights;

			};
		}
	}
}