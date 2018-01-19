#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "OpenGLTexture.h"

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

				std::unordered_map<HMEngine::OpenGL::OpenGLTexture*, std::vector<HMEngine::Components::MeshRenderer*>, HMEngine::OpenGL::OpenGLTexture::TextureHasher, HMEngine::OpenGL::OpenGLTexture::TextureEqualer> _meshTextures;
				std::vector<HMEngine::Components::TerrainRenderer*> _terrainRenderers;
				glm::vec3& _skyColor;
			};
		}
	}
}