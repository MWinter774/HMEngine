#include "GameObject.h"

#define MEMBER_OFFSET(s,m) ((char*)NULL + (offsetof(s,m)))

/*
bool HMEngine::Core::GameObject::operator==(const GameObject& go)
{
	if (go._pos == this->_pos && go._vertices == this->_vertices)
		return true;
	return false;
}
*/

void HMEngine::Core::GameObject::SetPos(const HMEngine::Core::Transform & transform)
{
	*this->_transform = transform;
};

void HMEngine::Core::GameObject::SetVertices(std::vector<glm::vec3> vertices)
{
	//glBindVertexArray(0);
	this->_vertices = vertices;
	this->_transform = new Transform;
	//glGenVertexArrays(1, &this->_vao);
	//glBindVertexArray(this->_vao);

}

void HMEngine::Core::GameObject::Draw(GLuint program, glm::mat4 mvp)
{
	glBindVertexArray(0);

	GLint positionAtribID = glGetAttribLocation(program, "in_position");
	GLint colorAtribID = glGetAttribLocation(program, "in_color");
	GLint uniformMVP = -1;
	uniformMVP = glGetUniformLocation(program, "MVP");

	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	GLuint vertexBuffer, indexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->_vertices), &_vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_Indices), g_Indices, GL_STATIC_DRAW);

	glVertexAttribPointer(positionAtribID, 3, GL_FLOAT, false, sizeof(this->_vertices), 0);
	glEnableVertexAttribArray(positionAtribID);
	glVertexAttribPointer(colorAtribID, 3, GL_FLOAT, false, sizeof(this->_color), 0);
	glEnableVertexAttribArray(colorAtribID);





	glUseProgram(program);
	glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, glm::value_ptr(mvp));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
	glColor3f(1, 0, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(positionAtribID);
	glDisableVertexAttribArray(colorAtribID);

}

