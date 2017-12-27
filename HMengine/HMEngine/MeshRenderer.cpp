#include "MeshRenderer.h"

HMEngine::Components::MeshRenderer::MeshRenderer(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices) : _vao(0), _vertices(vertices), _indices(indices)
{
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	glGenBuffers(NUM_BUFFERS, this->_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, (this->_vertices.size() * sizeof(this->_vertices[0])), &this->_vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo[VBO_INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (this->_indices.size() * sizeof(this->_indices[0])), &this->_indices[0], GL_STATIC_DRAW);

}

HMEngine::Components::MeshRenderer::~MeshRenderer()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteBuffers(2, this->_vbo);
	glDeleteBuffers(1, &this->_vao);
}

void HMEngine::Components::MeshRenderer::RenderEvent()
{
	glBindVertexArray(this->_vao);

	glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
}