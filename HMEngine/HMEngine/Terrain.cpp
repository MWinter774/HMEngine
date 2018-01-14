#include "Terrain.h"
#include "Transform.h"
#include "TerrainRenderer.h"
#include <glm/glm.hpp>
#include <vector>

HMEngine::Terrain::Terrain(const std::string& name, const glm::vec3& position, unsigned int size, const std::string& terrainTexturePath) : GameObject(name), _terrainRenderer(new HMEngine::Components::TerrainRenderer(size, terrainTexturePath))
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

