#include "RenderingEngine.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "OpenGLTexture.h"
#include "BasicShader.h"
#include "TerrainShader.h"
#include "GameObject.h"
#include "DirectionalLight.h"
#include "DirectionalLightShader.h"
#include "PointLight.h"
#include "PointLightShader.h"
#include "AmbientLightShader.h"
#include "GameSettings.h"
#include "TerrainRenderer.h"
#include <algorithm>

HMEngine::Core::Rendering::RenderingEngine& HMEngine::Core::Rendering::RenderingEngine::GetInstance()
{
	static HMEngine::Core::Rendering::RenderingEngine& instance = HMEngine::Core::Rendering::RenderingEngine();
	return instance;
}

void HMEngine::Core::Rendering::RenderingEngine::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(this->_skyColor.r, this->_skyColor.g, this->_skyColor.b, 1.0f);

	this->RenderMeshes();
	this->RenderTerrains();
	
	if (this->_doCleanup = (this->_directionalLights.size() > 0 || this->_pointLights.size() > 0))
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);
	}

	if (this->_directionalLights.size() > 0) //if there are any directional lights then render all the meshed with the directional lights effect on them
	{
		HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().Bind();
		for (auto& item : this->_meshTextures)
		{
			item.first->Bind();
			for (auto& mesh : item.second)
			{
				for (auto& directionalLight : _directionalLights)
				{
					HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(*directionalLight);
					HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
					HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(mesh->GetShineDamper(), mesh->GetReflectivity());
					mesh->DrawMesh();
				}
			}
		}
		for (auto& terrain : this->_terrainRenderers)
		{
			for (auto& directionalLight : _directionalLights)
			{
				HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(*directionalLight);
				HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(terrain->GetParent().GetTransform());
				HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(0.05f, 1.0f);
				terrain->BindTextures(); //Binds terrain textures
				terrain->DrawTerrain();
			}
		}
	}
	if (this->_pointLights.size() > 0) //if there are any point lights then render all the meshed with the point light effect on them
	{
		HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().Bind();
		for (auto& item : this->_meshTextures)
		{
			item.first->Bind();
			for (auto& mesh : item.second)
			{
				for (auto& pointLight : this->_pointLights)
				{
					HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(*pointLight);
					HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
					HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(mesh->GetShineDamper(), mesh->GetReflectivity());
					mesh->DrawMesh();
				}
			}
		}
		for (auto& terrain : this->_terrainRenderers)
		{
			for (auto& pointLight : this->_pointLights)
			{
				HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(*pointLight);
				HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(terrain->GetParent().GetTransform());
				HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(0.05f, 1.0f);
				terrain->BindTextures(); //Binds terrain textures
				terrain->DrawTerrain();
			}
		}
	}

	if (this->_doCleanup) //if there are some lights in the scene then load back the settings from blending the new lights
	{
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
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

HMEngine::Core::Rendering::RenderingEngine::RenderingEngine() : _meshTextures(), _skyColor(HMEngine::GameSettings::GetSkyColor()), _terrainRenderers(), _directionalLights(), _pointLights(), _doCleanup(false)
{
	//glCullFace(GL_BACK); //Causes the back of things not to be drawn
	//glEnable(GL_CULL_FACE); //Causes the back of things not to be drawn
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
}

HMEngine::Core::Rendering::RenderingEngine::~RenderingEngine()
{
}

void HMEngine::Core::Rendering::RenderingEngine::RenderMeshes() const
{
	/* Renders meshes */
	bool hadTransparency = false;
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().Bind();
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
			HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
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
}

void HMEngine::Core::Rendering::RenderingEngine::RenderTerrains() const
{
	/* Renders terrains */
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().Bind();
	for (auto& terrain : this->_terrainRenderers)
	{
		HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().UpdateUniforms(terrain->GetParent().GetTransform());
		terrain->BindTextures(); //Binds terrain textures
		terrain->DrawTerrain();
	}
}

void HMEngine::Core::Rendering::RenderingEngine::AddDirectionalLight(HMEngine::Components::DirectionalLight& directionalLight)
{
	_directionalLights.insert(&directionalLight);
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveDirectionalLight(HMEngine::Components::DirectionalLight& directionalLight)
{
	this->_directionalLights.erase(&directionalLight);
}

void HMEngine::Core::Rendering::RenderingEngine::AddPointLight(HMEngine::Components::PointLight& pointLight)
{
	this->_pointLights.insert(&pointLight);
}

void HMEngine::Core::Rendering::RenderingEngine::RemovePointLight(HMEngine::Components::PointLight& pointLight)
{
	this->_pointLights.erase(&pointLight);
}
