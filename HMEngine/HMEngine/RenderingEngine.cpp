#include "RenderingEngine.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "BasicShader.h"
#include "GameObject.h"
#include "DirectionalLight.h"
#include "DirectionalLightShader.h"
#include "PointLight.h"
#include "PointLightShader.h"
#include "AmbientLightShader.h"

HMEngine::Core::Rendering::RenderingEngine& HMEngine::Core::Rendering::RenderingEngine::GetInstance()
{
	static HMEngine::Core::Rendering::RenderingEngine& instance = HMEngine::Core::Rendering::RenderingEngine();
	return instance;
}

void HMEngine::Core::Rendering::RenderingEngine::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

	//HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().Bind();
	//for (auto& item : this->_textures)
	//{
	//	item.first->Bind();
	//	for (auto& mesh : item.second)
	//	{
	//		HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
	//		mesh->DrawMesh();
	//	}
	//}
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().Bind();
	for (auto& item : this->_textures)
	{
		item.first->Bind();
		for (auto& mesh : item.second)
		{
			HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
			mesh->DrawMesh();
		}
	}
	if (this->_doCleanup = (this->_directionalLights.size() > 0 || this->_pointLights.size() > 0))
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);
	}

	if (this->_directionalLights.size() > 0)
	{
		HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().Bind();
		for (auto& item : this->_textures)
		{
			item.first->Bind();
			for (auto& mesh : item.second)
			{
				for (auto& directionalLight : _directionalLights)
				{
					HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(*directionalLight);
					HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
					mesh->DrawMesh();
				}
			}
		}
	}
	if (this->_pointLights.size() > 0)
	{
		HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().Bind();
		for (auto& item : this->_textures)
		{
			item.first->Bind();
			for (auto& mesh : item.second)
			{
				for (auto& pointLight : this->_pointLights)
				{
					HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(*pointLight);
					HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
					mesh->DrawMesh();
				}
			}
		}
	}



	if (this->_doCleanup)
	{
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

}

void HMEngine::Core::Rendering::RenderingEngine::AddMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer)
{
	this->_textures[&meshRenderer.GetTexture()].push_back(&meshRenderer);
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer)
{
	int i = 0;
	for (auto mRenderer : this->_textures[&meshRenderer.GetTexture()])
	{
		if (mRenderer == &meshRenderer)
		{
			this->_textures[&meshRenderer.GetTexture()].erase(this->_textures[&meshRenderer.GetTexture()].begin() + i);
			if (this->_textures[&meshRenderer.GetTexture()].size() == 0)
				this->_textures.erase(&meshRenderer.GetTexture());
		}
		i++;
	}
}

HMEngine::Core::Rendering::RenderingEngine::RenderingEngine() : _textures(), _directionalLights(), _pointLights(), _doCleanup(false)
{
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
	//glCullFace(GL_BACK); //Causes the back of things not to be drawn
	//glEnable(GL_CULL_FACE); //Causes the back of things not to be drawn
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_TEXTURE_2D);
}

HMEngine::Core::Rendering::RenderingEngine::~RenderingEngine()
{
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
