#include "RenderingEngine.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "BasicShader.h"
#include "TerrainShader.h"
#include "GameObject.h"
#include "GameSettings.h"
#include "TerrainRenderer.h"
#include <algorithm>

HMEngine::Core::Rendering::RenderingEngine& HMEngine::Core::Rendering::RenderingEngine::GetInstance()
{
	static HMEngine::Core::Rendering::RenderingEngine& instance = HMEngine::Core::Rendering::RenderingEngine();
	return instance;
}

void HMEngine::Core::Rendering::RenderingEngine::Render() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(this->_skyColor.r, this->_skyColor.g, this->_skyColor.b, 1.0f);

	/* Renders meshes */
	bool hadTransparency = false;
	HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().Bind();
	for (auto& item : this->_meshTextures)
	{
		item.first->Bind();
		for (auto& mesh : item.second)
		{
			/* If the mesh has transparent texture then dont cull face */
			if (mesh->HasTransparency())
			{
				glDisable(GL_CULL_FACE);
				hadTransparency = true;
			}

			HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
			mesh->DrawMesh();

			/* If the mesh had transparent texture then turn on cull */
			if (hadTransparency)
			{
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				hadTransparency = false;
			}
		}
	}

	/* Renders terrains */
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().Bind();
	for (auto& item : this->_terrainTextures)
	{
		item.first->Bind();
		for (auto& terrain : item.second)
		{
			item.first->Bind();
			HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().UpdateUniforms(terrain->GetParent().GetTransform());
			terrain->DrawTerrain();
		}
	}
}

void HMEngine::Core::Rendering::RenderingEngine::AddMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer)
{
	this->_meshTextures[&meshRenderer.GetTexture()].push_back(&meshRenderer);
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer)
{
	int i = 0;
	for (auto mRenderer : this->_meshTextures[&meshRenderer.GetTexture()])
	{
		if (mRenderer == &meshRenderer)
		{
			this->_meshTextures[&meshRenderer.GetTexture()].erase(this->_meshTextures[&meshRenderer.GetTexture()].begin() + i);
			if (this->_meshTextures[&meshRenderer.GetTexture()].size() == 0)
				this->_meshTextures.erase(&meshRenderer.GetTexture());
		}
		i++;
	}
}

void HMEngine::Core::Rendering::RenderingEngine::AddTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer)
{
	this->_terrainTextures[&terrainRenderer.GetTexture()].push_back(&terrainRenderer);
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer)
{
	int i = 0;
	for (auto tRenderer : this->_terrainTextures[&terrainRenderer.GetTexture()])
	{
		if (tRenderer == &terrainRenderer)
		{
			this->_terrainTextures[&terrainRenderer.GetTexture()].erase(this->_terrainTextures[&terrainRenderer.GetTexture()].begin() + i);
			if (this->_terrainTextures[&terrainRenderer.GetTexture()].size() == 0)
				this->_terrainTextures.erase(&terrainRenderer.GetTexture());
		}
		i++;
	}
}

HMEngine::Core::Rendering::RenderingEngine::RenderingEngine() : _meshTextures(), _skyColor(HMEngine::GameSettings::GetSkyColor()), _terrainTextures()
{
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

HMEngine::Core::Rendering::RenderingEngine::~RenderingEngine()
{
}