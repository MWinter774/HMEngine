#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Texture.h"

namespace HMEngine
{
	namespace Components
	{
		class MeshRenderer;
		class TerrainRenderer;
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
				void AddTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer);
				void RemoveTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer);

			private:
				RenderingEngine();
				~RenderingEngine();
				RenderingEngine(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;
				HMEngine::Core::Rendering::RenderingEngine& operator=(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;

				std::unordered_map<HMEngine::OpenGL::Texture*, std::vector<HMEngine::Components::MeshRenderer*>, HMEngine::OpenGL::Texture::TextureHasher, HMEngine::OpenGL::Texture::TextureEqualer> _meshTextures;
				std::unordered_map<HMEngine::OpenGL::Texture*, std::vector<HMEngine::Components::TerrainRenderer*>, HMEngine::OpenGL::Texture::TextureHasher, HMEngine::OpenGL::Texture::TextureEqualer> _terrainTextures;
				glm::vec3& _skyColor;
			};
		}
	}
}