#include "Terrain.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include <glm/glm.hpp>
#include <vector>

HMEngine::Terrain::Terrain(const std::string& name, const glm::vec3& position, unsigned int size, const std::string& texturePath) : GameObject(name), _terrainSize(size), _meshRenderer(nullptr), _vertexCount(unsigned int(0.16*_terrainSize))
{
	this->_transform->SetPosition(position);
	this->_meshRenderer = HMEngine::Terrain::GenerateTerrain(this->_terrainSize, this->_vertexCount, texturePath);
	this->AddComponent(*this->_meshRenderer);
}

HMEngine::Terrain::~Terrain()
{
	delete this->_meshRenderer;
}

HMEngine::Terrain::Terrain(const HMEngine::Terrain& other) : GameObject(other), _terrainSize(other._terrainSize), _vertexCount(other._vertexCount)
{
	this->_meshRenderer = new HMEngine::Components::MeshRenderer(*other._meshRenderer);
}

HMEngine::Terrain & HMEngine::Terrain::operator=(const HMEngine::Terrain& other)
{
	if (this != &other)
	{
		this->_terrainSize = other._terrainSize;
		this->_vertexCount = other._vertexCount;
		delete this->_meshRenderer;
		this->_meshRenderer = new HMEngine::Components::MeshRenderer(*other._meshRenderer);
	}

	return *this;
}

HMEngine::Components::MeshRenderer* HMEngine::Terrain::GenerateTerrain(unsigned int terrainSize, unsigned int vertexCount, const std::string& texturePath)
{
	int count = vertexCount * vertexCount;
	std::vector<glm::vec3> vertices = std::vector<glm::vec3>(count * 3);
	float* normals = new float[count * 3];
	std::vector<glm::vec2> textureCoords = std::vector<glm::vec2>(count * 2);
	std::vector<GLuint> indices = std::vector<GLuint>(6 * (vertexCount - 1)*(vertexCount - 1));
	int vertexPointer = 0;
	for (unsigned int i = 0; i < vertexCount; i++)
	{
		for (unsigned int j = 0; j < vertexCount; j++)
		{
			vertices[vertexPointer] = glm::vec3(float(j) / ((float)vertexCount - 1) * terrainSize, 0, (float)i / ((float)vertexCount - 1) * terrainSize);
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer] = glm::vec2((float)j / ((float)vertexCount - 1) * 40, (float)i / ((float)vertexCount - 1) * 40);
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (unsigned int gz = 0; gz < vertexCount - 1; gz++)
	{
		for (unsigned int gx = 0; gx < vertexCount - 1; gx++)
		{
			int topLeft = (gz * vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}

	delete normals;
	return new HMEngine::Components::MeshRenderer(vertices, indices, textureCoords, texturePath);
}