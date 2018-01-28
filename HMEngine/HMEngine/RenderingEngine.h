#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "OpenGLTexture.h"
#include "DirectionalLight.h"
#include <unordered_set>

namespace HMEngine
{
	namespace Components
	{
		class MeshRenderer;
		class DirectionalLight;
		class PointLight;
		class TerrainRenderer;
	}
	namespace Core
	{
		class GameObject;
		class Transform;

		namespace Rendering
		{
			class RenderingEngine
			{
			public:
				static HMEngine::Core::Rendering::RenderingEngine& GetInstance();

				void Render();

				void AddMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer);
				void RemoveMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer);
				void AddTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer);
				void RemoveTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer);

				void AddDirectionalLight(HMEngine::Components::DirectionalLight& directionalLight);
				void RemoveDirectionalLight(HMEngine::Components::DirectionalLight& directionalLight);

				void AddPointLight(HMEngine::Components::PointLight& pointLight);
				void RemovePointLight(HMEngine::Components::PointLight& pointLight);


			private:
				enum term { A = 0, B, C, D };

				bool _doCleanup;

				RenderingEngine();
				~RenderingEngine();
				RenderingEngine(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;
				HMEngine::Core::Rendering::RenderingEngine& operator=(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;

				std::unordered_map<HMEngine::OpenGL::OpenGLTexture*, std::vector<HMEngine::Components::MeshRenderer*>, HMEngine::OpenGL::OpenGLTexture::TextureHasher, HMEngine::OpenGL::OpenGLTexture::TextureEqualer> _meshTextures;
				std::unordered_set<HMEngine::Components::DirectionalLight*> _directionalLights;
				std::unordered_set<HMEngine::Components::PointLight*> _pointLights;

				std::list<HMEngine::Components::MeshRenderer*> _meshesToRender;
				std::vector<HMEngine::Components::TerrainRenderer*> _terrainRenderers;
				glm::vec3& _skyColor;

				std::unordered_map<HMEngine::OpenGL::OpenGLTexture*, std::vector<HMEngine::Components::MeshRenderer*>, HMEngine::OpenGL::OpenGLTexture::TextureHasher, HMEngine::OpenGL::OpenGLTexture::TextureEqualer> _unseenObjects;


				void RenderMeshes() const;
				void RenderTerrains() const;

				void CullFrustrum();

				bool IsObjectVisible(const glm::mat4& objectMVPMatrix, const glm::vec3& objectPos, float radius);

				float Test(HMEngine::Core::Transform& transform) const;
			};
		}
	}
}