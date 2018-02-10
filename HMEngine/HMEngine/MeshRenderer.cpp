#include "MeshRenderer.h"
#include "GameObject.h"
#include "BasicShader.h"
#include "Texture.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include <glm/gtx/string_cast.hpp>

HMEngine::Components::MeshRenderer::MeshRenderer(const std::string& meshPath, const std::string& texturePath, float shineDamper, float reflectivity) : _texturePath(texturePath), _meshPath(meshPath), _shineDamper(shineDamper), _reflectivity(reflectivity)
{
}

HMEngine::Components::MeshRenderer::~MeshRenderer()
{
	if (this->_isAttachedToGameObject)
	{
		HMEngine::Core::Rendering::RenderingEngine::GetInstance().RemoveMeshRenderer(*this);
		HMEngine::Core::Physics::PhysicsEngine::RemoveGameObjectCollider(&this->_mesh->GetBoundingSphere());
		delete this->_mesh;
		delete this->_texture;
	}
}

HMEngine::Components::MeshRenderer::MeshRenderer(const HMEngine::Components::MeshRenderer& other)
{
	this->_texturePath = other._texturePath;
	this->_meshPath = other._meshPath;
	this->_shineDamper = other._shineDamper;
	this->_reflectivity = other._reflectivity;
	if (other._isAttachedToGameObject)
	{
		this->_texture = new HMEngine::OpenGL::Texture(*other._texture);
		this->_mesh = new HMEngine::Core::Mesh(*other._mesh);
		this->_isAttachedToGameObject = other._isAttachedToGameObject;

		HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddMeshRenderer(*this);
	}
}

HMEngine::Components::MeshRenderer& HMEngine::Components::MeshRenderer::operator=(const HMEngine::Components::MeshRenderer& other)
{
	if (this != &other)
	{
		this->_texturePath = other._texturePath;
		this->_shineDamper = other._shineDamper;
		this->_reflectivity = other._reflectivity;
		this->_meshPath = other._meshPath;
		if (other._isAttachedToGameObject)
		{
			delete this->_texture;
			this->_texture = new HMEngine::OpenGL::Texture(*other._texture);
			delete this->_mesh;
			this->_mesh = new HMEngine::Core::Mesh(*other._mesh);
			this->_isAttachedToGameObject = other._isAttachedToGameObject;
			HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddMeshRenderer(*this);
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
	this->_texture = new HMEngine::OpenGL::Texture(this->_texturePath);
	this->_mesh = new HMEngine::Core::Mesh(this->_meshPath);
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddMeshRenderer(*this);
	HMEngine::Core::Physics::PhysicsEngine::AddGameObjectCollider(&this->_mesh->GetBoundingSphere(), this->_parentObject);
}

void HMEngine::Components::MeshRenderer::SetTexture(const std::string& texturePath)
{
	delete this->_texture;
	this->_texture = new HMEngine::OpenGL::Texture(this->_texturePath);
}
