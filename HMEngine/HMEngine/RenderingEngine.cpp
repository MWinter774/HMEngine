#include "RenderingEngine.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "BasicShader.h"
#include "GameObject.h"

HMEngine::Core::Rendering::RenderingEngine& HMEngine::Core::Rendering::RenderingEngine::GetInstance()
{
	static HMEngine::Core::Rendering::RenderingEngine& instance = HMEngine::Core::Rendering::RenderingEngine();
	return instance;
}

void HMEngine::Core::Rendering::RenderingEngine::Render(const std::vector<HMEngine::Core::GameObject*>& gameObjects) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().Bind();
	for (auto& item : this->_textures)
	{
		item.first->Bind();
		for(auto& mesh : item.second)
		{
			HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
			mesh->DrawMesh();
		}
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

HMEngine::Core::Rendering::RenderingEngine::RenderingEngine() : _textures()
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
}

HMEngine::Core::Rendering::RenderingEngine::~RenderingEngine()
{
}