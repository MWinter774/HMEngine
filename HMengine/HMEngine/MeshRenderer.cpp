#include "MeshRenderer.h"
#include "GameObject.h"
#include "BasicShader.h"
#include "Texture.h"
#include "RenderingEngine.h"
#include <glm/gtx/string_cast.hpp>

HMEngine::Components::MeshRenderer::MeshRenderer(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, const std::vector<glm::vec2>& uvs, const std::string& texturePath) : _vao(0), _vertices(vertices), _indices(indices), _uvs(uvs), _isAddedToRenderingEngine(false), _texturePath(texturePath)
{
}

HMEngine::Components::MeshRenderer::MeshRenderer(const std::string& meshPath, const std::string& texturePath) : _vao(0), _isAddedToRenderingEngine(false), _texturePath(texturePath), _meshPath(meshPath)
{
	this->_mesh = new HMEngine::Core::Mesh(meshPath);
}

HMEngine::Components::MeshRenderer::~MeshRenderer()
{
	if (this->_isAddedToRenderingEngine)
	{
		HMEngine::Core::Rendering::RenderingEngine::GetInstance().RemoveMeshRenderer(*this);
		glBindVertexArray(this->_vao);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDeleteBuffers(2, this->_vbo);
		glDeleteBuffers(1, &this->_vao);
		glBindVertexArray(0);
		delete this->_mesh;
	}
}

HMEngine::Components::MeshRenderer::MeshRenderer(const HMEngine::Components::MeshRenderer& other)
{
	this->_mesh = new HMEngine::Core::Mesh(*other._mesh);
	if (other._isAddedToRenderingEngine)
	{
		this->_vertices = other._vertices;
		this->_indices = other._indices;
		this->_uvs = other._uvs;
		this->_texturePath = other._texturePath;
		this->_texture = new HMEngine::Components::Texture(*other._texture);
		this->_isAddedToRenderingEngine = other._isAddedToRenderingEngine;

		HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddMeshRenderer(*this);

		this->InitBuffers();
	}
	else
	{
		this->_vertices = other._vertices;
		this->_indices = other._indices;
		this->_uvs = other._uvs;
		this->_texturePath = other._texturePath;
	}
}

HMEngine::Components::MeshRenderer& HMEngine::Components::MeshRenderer::operator=(const HMEngine::Components::MeshRenderer& other)
{
	if (this != &other)
	{
		delete this->_mesh;
		this->_mesh = new HMEngine::Core::Mesh(*other._mesh);
		if (other._isAddedToRenderingEngine)
		{
			this->_vertices = other._vertices;
			this->_indices = other._indices;
			this->_uvs = other._uvs;
			this->_texturePath = other._texturePath;
			*this->_texture = *other._texture;
			this->_isAddedToRenderingEngine = other._isAddedToRenderingEngine;
			HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddMeshRenderer(*this);

			this->InitBuffers();
		}
		else
		{
			this->_vertices = other._vertices;
			this->_indices = other._indices;
			this->_uvs = other._uvs;
			this->_texturePath = other._texturePath;
		}
	}

	return *this;
}

void HMEngine::Components::MeshRenderer::DrawMesh()
{
	glBindVertexArray(this->_vao);

	glDrawArrays(GL_TRIANGLES, 0, this->_mesh->GetVertices().size());

	glBindVertexArray(0);
}

void HMEngine::Components::MeshRenderer::AttachToGameObjectEvent()
{
	this->_isAddedToRenderingEngine = true;
	this->_texture = new HMEngine::Components::Texture(this->_texturePath);
	this->InitBuffers();
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddMeshRenderer(*this);
}

void HMEngine::Components::MeshRenderer::InitBuffers()
{

	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	glGenBuffers(NUM_BUFFERS, this->_vbo);

	/* Generates the vertices buffer */
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, this->_mesh->GetVertices().size() * sizeof((this->_mesh->GetVertices())[0]), &this->_mesh->GetVertices()[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/* Generates the uv's buffer */
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_TEXTURE_COORDS]);
	glBufferData(GL_ARRAY_BUFFER, (this->_mesh->GetUVs().size() * sizeof(this->_mesh->GetUVs()[0])), &this->_mesh->GetUVs()[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	/* Generates the indices buffer */
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo[VBO_INDICES]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, (this->_mesh->ge * 3 * sizeof(this->_mesh->GetFaceIndices()[0].vertexIndex[0])), &this->_mesh->GetFaceIndices[, GL_STATIC_DRAW);
}