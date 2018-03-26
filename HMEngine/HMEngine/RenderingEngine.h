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
	namespace UI
	{
		class Quad;
		class Label;
		class Billboard;
	}
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
			namespace Shaders
			{
				class AmbientLightShader;
				class DirectionalLightShader;
				class LabelShader;
				class PointLightShader;
				class TerrainShader;
				class UIShader;
				class BillboardQuadShader;
				class BillboardLabelShader;
			}

			class RenderingEngine
			{
			public:
				typedef struct
			{
				HMEngine::UI::Label* label;
				HMEngine::UI::Quad* quad;
			} Quad;

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

				void AddUI(HMEngine::UI::Quad& ui);
				void RemoveUI(HMEngine::UI::Quad& ui);

				void AddBillboard(HMEngine::UI::Billboard& billboard);
				void RemoveBillboard(HMEngine::UI::Billboard& billboard);

				void BringToFront(HMEngine::UI::Quad* ui);


			private:
				enum term { A = 0, B, C, D };

				bool _doCleanupForMeshes;
				bool _doCleanupForQuads;
				bool _doCleanupForBillboards;
				HMEngine::Core::Rendering::Shaders::AmbientLightShader* _ambientShader;
				HMEngine::Core::Rendering::Shaders::DirectionalLightShader* _directionalLightShader;
				HMEngine::Core::Rendering::Shaders::LabelShader* _labelShader;
				HMEngine::Core::Rendering::Shaders::PointLightShader* _pointLightShader;
				HMEngine::Core::Rendering::Shaders::TerrainShader* _terrainShader;
				HMEngine::Core::Rendering::Shaders::UIShader* _UIShader;
				HMEngine::Core::Rendering::Shaders::BillboardQuadShader* _billboardQuadShader;
				HMEngine::Core::Rendering::Shaders::BillboardLabelShader* _billboardLabelShader;

				RenderingEngine();
				~RenderingEngine();
				RenderingEngine(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;
				HMEngine::Core::Rendering::RenderingEngine& operator=(const HMEngine::Core::Rendering::RenderingEngine& other) = delete;

				std::unordered_map<HMEngine::OpenGL::OpenGLTexture*, std::vector<HMEngine::Components::MeshRenderer*>, HMEngine::OpenGL::OpenGLTexture::TextureHasher, HMEngine::OpenGL::OpenGLTexture::TextureEqualer> _meshTextures;
				std::unordered_set<HMEngine::Components::DirectionalLight*> _directionalLights;
				std::unordered_set<HMEngine::Components::PointLight*> _pointLights;
				std::unordered_set<HMEngine::UI::Label*> _labels;
				std::vector<RenderingEngine::Quad> _quads;
				std::unordered_set<HMEngine::UI::Billboard*> _billboards;

				std::list<HMEngine::Components::MeshRenderer*> _meshesToRender;
				std::vector<HMEngine::Components::TerrainRenderer*> _terrainRenderers;
				glm::vec3& _skyColor;

				std::unordered_map<HMEngine::OpenGL::OpenGLTexture*, std::vector<HMEngine::Components::MeshRenderer*>, HMEngine::OpenGL::OpenGLTexture::TextureHasher, HMEngine::OpenGL::OpenGLTexture::TextureEqualer> _unseenObjects;

				void RenderMeshes() const;
				void RenderTerrains() const;
				void RenderQuads();
				void RenderBillboards();

				void CullFrustrum();

				bool IsObjectVisible(const glm::mat4& objectMVPMatrix, const glm::vec3& objectPos, float radius);

				void RenderQuad(HMEngine::UI::Quad* q);
				void RenderLabel(HMEngine::UI::Quad* q);
			};
		}
	}
}