#include "MeshRenderer.h"
#include "GameObject.h"
#include "BasicShader.h"
#include "Texture.h"
#include "RenderingEngine.h"
#include <glm/gtx/string_cast.hpp>

HMEngine::Components::MeshRenderer::MeshRenderer(const std::string& meshPath, const std::string& texturePath, float shineDamper, float reflectivity) : _isAddedToRenderingEngine(false), _texturePath(texturePath), _meshPath(meshPath), _shineDamper(shineDamper), _reflectivity(reflectivity)
{
}

HMEngine::Components::MeshRenderer::~MeshRenderer()
{
	if (this->_isAddedToRenderingEngine)
	{
		HMEngine::Core::Rendering::RenderingEngine::GetInstance().RemoveMeshRenderer(*this);
		delete this->_mesh;
	}
}

HMEngine::Components::MeshRenderer::MeshRenderer(const HMEngine::Components::MeshRenderer& other)
{
	if (other._isAddedToRenderingEngine)
	{
		this->_texturePath = other._texturePath;
		this->_texture = new HMEngine::Components::Texture(*other._texture);
		this->_meshPath = other._meshPath;
		this->_mesh = new HMEngine::Core::Mesh(*other._mesh);
		this->_isAddedToRenderingEngine = other._isAddedToRenderingEngine;
		this->_shineDamper = other._shineDamper;
		this->_reflectivity = other._reflectivity;

		HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddMeshRenderer(*this);
	}
	else
	{
		this->_meshPath = other._meshPath;
		this->_texturePath = other._texturePath;
		this->_shineDamper = other._shineDamper;
		this->_reflectivity = other._reflectivity;
	}
}

HMEngine::Components::MeshRenderer& HMEngine::Components::MeshRenderer::operator=(const HMEngine::Components::MeshRenderer& other)
{
	if (this != &other)
	{
		if (other._isAddedToRenderingEngine)
		{
			this->_texturePath = other._texturePath;
			*this->_texture = *other._texture;
			this->_meshPath = other._meshPath;
			delete this->_mesh;
			this->_mesh = new HMEngine::Core::Mesh(*other._mesh);
			this->_isAddedToRenderingEngine = other._isAddedToRenderingEngine;
			HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddMeshRenderer(*this);
			this->_shineDamper = other._shineDamper;
			this->_reflectivity = other._reflectivity;
		}
		else
		{
			this->_meshPath = other._meshPath;
			this->_texturePath = other._texturePath;
			this->_shineDamper = other._shineDamper;
			this->_reflectivity = other._reflectivity;
		}
	}

	return *this;
}

void HMEngine::Components::MeshRenderer::DrawMesh()
{
	this->_mesh->Draw();
}

void HMEngine::Components::MeshRenderer::AttachToGameObjectEvent()
{
	this->_isAddedToRenderingEngine = true;
	this->_texture = new HMEngine::Components::Texture(this->_texturePath);
	this->_mesh = new HMEngine::Core::Mesh(this->_meshPath);
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddMeshRenderer(*this);
}

void HMEngine::Components::MeshRenderer::SetTexture(const std::string& texturePath)
{
	this->_texture = new HMEngine::Components::Texture(this->_texturePath);
}
