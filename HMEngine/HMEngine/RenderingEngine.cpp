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

		/* If the mesh has transparent texture then dont cull face */
		if (item.first->HasTransparency())
		{
			glDisable(GL_CULL_FACE);
			hadTransparency = true;
		}
		for (auto& mesh : item.second)
		{
			HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
			mesh->DrawMesh();
		}
		/* If the mesh had transparent texture then turn on cull */
		if (hadTransparency)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			hadTransparency = false;
		}
	}

	/* Renders terrains */
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().Bind();
	for (auto& terrain : this->_terrainRenderers)
	{
		HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().UpdateUniforms(terrain->GetParent().GetTransform());
		terrain->BindTextures(); //Binds terrain textures
		terrain->DrawTerrain();
	}
}

void HMEngine::Core::Rendering::RenderingEngine::AddMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer)
{
	this->_meshTextures[&meshRenderer.GetTexture().GetOpenGLTexture()].push_back(&meshRenderer);
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer)
{
	int i = 0;
	for (auto mRenderer : this->_meshTextures[&meshRenderer.GetTexture().GetOpenGLTexture()])
	{
		if (mRenderer == &meshRenderer)
		{
			this->_meshTextures[&meshRenderer.GetTexture().GetOpenGLTexture()].erase(this->_meshTextures[&meshRenderer.GetTexture().GetOpenGLTexture()].begin() + i);
			if (this->_meshTextures[&meshRenderer.GetTexture().GetOpenGLTexture()].size() == 0)
				this->_meshTextures.erase(&meshRenderer.GetTexture().GetOpenGLTexture());
		}
		i++;
	}
}

void HMEngine::Core::Rendering::RenderingEngine::AddTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer)
{
	this->_terrainRenderers.push_back(&terrainRenderer);
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer)
{
	this->_terrainRenderers.erase(std::remove(this->_terrainRenderers.begin(), this->_terrainRenderers.end(), &terrainRenderer), this->_terrainRenderers.end());
}

HMEngine::Core::Rendering::RenderingEngine::RenderingEngine() : _meshTextures(), _skyColor(HMEngine::GameSettings::GetSkyColor()), _terrainRenderers()
{
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

HMEngine::Core::Rendering::RenderingEngine::~RenderingEngine()
{
}