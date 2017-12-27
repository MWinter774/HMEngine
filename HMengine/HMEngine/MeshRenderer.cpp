#include "MeshRenderer.h"

HMEngine::Components::MeshRenderer::MeshRenderer(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, const std::vector<glm::vec2>& uvs, const std::string& texturePath) : _vao(0), _vertices(vertices), _indices(indices), _uvs(uvs),_texture(new HMEngine::Components::Texture(texturePath))
{
	this->InitBuffers();
}

HMEngine::Components::MeshRenderer::~MeshRenderer()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(2, this->_vbo);
	glDeleteBuffers(1, &this->_vao);
	delete this->_texture;
}

HMEngine::Components::MeshRenderer::MeshRenderer(const HMEngine::Components::MeshRenderer& other)
{
	this->_vertices = other._vertices;
	this->_indices = other._indices;
	this->_uvs = other._uvs;
	this->_texture = new HMEngine::Components::Texture(*other._texture);

	this->InitBuffers();
}

HMEngine::Components::MeshRenderer& HMEngine::Components::MeshRenderer::operator=(const HMEngine::Components::MeshRenderer& other)
{
	if (this != &other)
	{
		this->_vertices = other._vertices;
		this->_indices = other._indices;
		this->_uvs = other._uvs;
		*this->_texture = *other._texture;

		this->InitBuffers();
	}

	return *this;
}

void HMEngine::Components::MeshRenderer::RenderEvent()
{
	HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().Bind();
	HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().UpdateUniforms(this->_parentObject->GetTransform());
	this->_texture->Bind();

	glBindVertexArray(this->_vao);

	glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
}

void HMEngine::Components::MeshRenderer::InitBuffers()
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
