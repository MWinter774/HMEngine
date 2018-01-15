#include "TerrainRenderer.h"
#include "Texture.h"
#include "RenderingEngine.h"

HMEngine::Components::TerrainRenderer::TerrainRenderer(unsigned int size, const std::string& terrainTexturePath) : _terrainSize(size), _vertexCount(unsigned int(0.16*_terrainSize)), _texture(nullptr), _isAddedToRenderingEngine(false), _texturePath(terrainTexturePath)
{
	int count = this->_vertexCount * this->_vertexCount;
	this->_vertices = std::vector<glm::vec3>(count * 3);
	this->_uvs = std::vector<glm::vec2>(count * 2);
	this->_indices = std::vector<GLuint>(6 * (this->_vertexCount - 1) * (this->_vertexCount - 1));
	this->GenerateTerrain();
}

HMEngine::Components::TerrainRenderer::~TerrainRenderer()
{
	if (this->_isAddedToRenderingEngine)
	{
		HMEngine::Core::Rendering::RenderingEngine::GetInstance().RemoveTerrainRenderer(*this);
		glBindVertexArray(this->_vao);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDeleteBuffers(2, this->_vbo);
		glDeleteBuffers(1, &this->_vao);
		glBindVertexArray(0);
	}
}

HMEngine::Components::TerrainRenderer::TerrainRenderer(const HMEngine::Components::TerrainRenderer& other)
{
	this->_vertices = other._vertices;
	this->_indices = other._indices;
	this->_uvs = other._uvs;
	this->_texturePath = other._texturePath;
	if (other._isAddedToRenderingEngine)
	{
		this->_texture = new HMEngine::OpenGL::Texture(*other._texture);
		this->_isAddedToRenderingEngine = other._isAddedToRenderingEngine;

		HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddTerrainRenderer(*this);

		this->InitBuffers();
	}
}

HMEngine::Components::TerrainRenderer& HMEngine::Components::TerrainRenderer::operator=(const HMEngine::Components::TerrainRenderer& other)
{
	if (this != &other)
	{
		this->_vertices = other._vertices;
		this->_indices = other._indices;
		this->_uvs = other._uvs;
		this->_texturePath = other._texturePath;
		if (other._isAddedToRenderingEngine)
		{
			*this->_texture = *other._texture;
			this->_isAddedToRenderingEngine = other._isAddedToRenderingEngine;
			HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddTerrainRenderer(*this);

			this->InitBuffers();
		}
	}

	return *this;
}

void HMEngine::Components::TerrainRenderer::AttachToGameObjectEvent()
{
	this->_isAddedToRenderingEngine = true;
	this->_texture = new HMEngine::OpenGL::Texture(this->_texturePath);
	this->InitBuffers();
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddTerrainRenderer(*this);
}

HMEngine::Components::Component* HMEngine::Components::TerrainRenderer::Clone()
{
	return new HMEngine::Components::TerrainRenderer(*this);
}

void HMEngine::Components::TerrainRenderer::DrawTerrain() const
{
	glBindVertexArray(this->_vao);

	glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void HMEngine::Components::TerrainRenderer::GenerateTerrain()
{
	int count = this->_vertexCount * this->_vertexCount;
	float* normals = new float[count * 3];
	int vertexPointer = 0;
	for (unsigned int i = 0; i < this->_vertexCount; i++)
	{
		for (unsigned int j = 0; j < this->_vertexCount; j++)
		{
			this->_vertices[vertexPointer] = glm::vec3(float(j) / ((float)this->_vertexCount - 1) * this->_terrainSize, 0, (float)i / ((float)this->_vertexCount - 1) * this->_terrainSize);
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			this->_uvs[vertexPointer] = glm::vec2((float)j / ((float)this->_vertexCount - 1), (float)i / ((float)this->_vertexCount - 1));
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (unsigned int gz = 0; gz < this->_vertexCount - 1; gz++)
	{
		for (unsigned int gx = 0; gx < this->_vertexCount - 1; gx++)
		{
			int topLeft = (gz * this->_vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * this->_vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			this->_indices[pointer++] = topLeft;
			this->_indices[pointer++] = bottomLeft;
			this->_indices[pointer++] = topRight;
			this->_indices[pointer++] = topRight;
			this->_indices[pointer++] = bottomLeft;
			this->_indices[pointer++] = bottomRight;
		}
	}

	delete normals;
}

void HMEngine::Components::TerrainRenderer::InitBuffers()
{
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	glGenBuffers(NUM_BUFFERS, this->_vbo);

	/* Generates the vertices buffer */
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, (this->_vertices.size() * sizeof(this->_vertices[0])), &this->_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/* Generates the uv's buffer */
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_TEXTURE_COORDS]);
	glBufferData(GL_ARRAY_BUFFER, (this->_uvs.size() * sizeof(this->_uvs[0])), &this->_uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/* Generates the indices buffer */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo[VBO_INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (this->_indices.size() * sizeof(this->_indices[0])), &this->_indices[0], GL_STATIC_DRAW);
}
