#include "GameObject.h"

HMEngine::Core::GameObject::GameObject(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices) : _transform(new HMEngine::Core::Transform()), _vertices(vertices), _indices(indices)
{
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	glGenBuffers(2, this->_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, (this->_vertices.size() * sizeof(this->_vertices[0])), &this->_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (this->_indices.size() * sizeof(this->_indices[0])), &this->_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

HMEngine::Core::GameObject::~GameObject()
{
	delete this->_transform;
}

HMEngine::Core::GameObject::GameObject(const HMEngine::Core::GameObject& other) : GameObject(other.GetVertices(), other.GetIndices())
{
	this->SetTransform(other.GetTransform());
}

HMEngine::Core::GameObject& HMEngine::Core::GameObject::operator=(const HMEngine::Core::GameObject& other)
{
	if (this != &other)
	{
		*this = HMEngine::Core::GameObject(other.GetVertices(), other.GetIndices());
		this->SetTransform(other.GetTransform());
	}

	return *this;
}

void HMEngine::Core::GameObject::SetTransform(HMEngine::Core::Transform& transform)
{
	*this->_transform = transform;
};

void HMEngine::Core::GameObject::SetVertices(std::vector<glm::vec3> vertices)
{
	this->_vertices = vertices;
}

void HMEngine::Core::GameObject::SetIndices(std::vector<GLuint> indices)
{
	this->_indices = indices; 
}

void HMEngine::Core::GameObject::Draw() const
{
	glBindVertexArray(this->_vao);

	glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "OpenGL error: " << err << std::endl;
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
}

void HMEngine::Core::GameObject::AddComponent(HMEngine::Components::Component* component)
{
	component->_parentObject = this;
	this->_components.push_back(component);
}