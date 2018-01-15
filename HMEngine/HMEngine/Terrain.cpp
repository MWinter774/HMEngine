#include "Terrain.h"
#include "Transform.h"
#include "TerrainRenderer.h"
#include <glm/glm.hpp>
#include <vector>

HMEngine::Terrain::Terrain(const std::string& name, const glm::vec3& position, unsigned int size, const std::string& backroundTextureFilePath, const std::string& rTextureFilePath, const std::string& gTextureFilePath, const std::string& bTextureFilePath, const std::string& blendMapFilePath) : GameObject(name), _terrainRenderer(new HMEngine::Components::TerrainRenderer(size, backroundTextureFilePath, rTextureFilePath, gTextureFilePath, bTextureFilePath, blendMapFilePath))
{
	this->_transform->SetPosition(position);
	this->AddComponent(*this->_terrainRenderer);
}

HMEngine::Terrain::Terrain(const std::string& name, const glm::vec3& position, unsigned int size, const std::string& texturePath) : GameObject(name), _terrainRenderer(new HMEngine::Components::TerrainRenderer(size, texturePath))
{
	this->_transform->SetPosition(position);
	this->AddComponent(*this->_terrainRenderer);
}

HMEngine::Terrain::~Terrain()
{
	delete this->_terrainRenderer;
}

HMEngine::Terrain::Terrain(const HMEngine::Terrain& other) : GameObject(other)
{
	this->_terrainRenderer = new HMEngine::Components::TerrainRenderer(*other._terrainRenderer);
}

HMEngine::Terrain& HMEngine::Terrain::operator=(const HMEngine::Terrain& other)
{
	if (this != &other)
	{
		delete this->_terrainRenderer;
		this->_terrainRenderer = new HMEngine::Components::TerrainRenderer(*other._terrainRenderer);
	}

	return *this;
}

