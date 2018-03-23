#include "Transform.h"
#include "Camera.h"
#include "GameSettings.h"
#include "GL\glew.h"
#include <iostream>

HMEngine::Core::Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : _position(position), _rotation(rotation), _scale(scale)
{
	this->UpdateTranslationMatrix();
	this->UpdateRotationMatrix();
	this->UpdateScaleMatrix();
}

HMEngine::Core::Transform::~Transform()
{
}

int j = 0;
void HMEngine::Core::Transform::LookAt(const glm::vec3& dst)
{
	//glm::mat4 transformation = glm::inverse(glm::lookAt(this->_position, glm::vec3(dst), glm::vec3(0, 1, 0)));
	//const GLfloat* transformationMatrix = glm::value_ptr(transformation);

	//float a = transformationMatrix[0];
	//float b = transformationMatrix[1];
	//float c = transformationMatrix[2];
	////float d = transformationMatrix[3];

	//float e = transformationMatrix[4];
	//float f = transformationMatrix[5];
	//float g = transformationMatrix[6];
	////float h = transformationMatrix[7];

	//float i = transformationMatrix[8];
	//float j = transformationMatrix[9];
	//float k = transformationMatrix[10];
	////float l = transformationMatrix[11];

	///*float sx = float(glm::vec3(a, e, i).length());
	//float sy = float(glm::vec3(b, f, j).length());
	//float sz = float(glm::vec3(c, g, k).length());*/

	//float sx = this->_scale.x;
	//float sy = this->_scale.y;
	//float sz = this->_scale.z;

	//glm::mat4 rotationMatrix = { a / sx, b / sy, c / sz, 0.0f,
	//							e / sx, f / sy, g / sz, 0.0f,
	//							i / sx, j / sy, k / sz, 0.0f,
	//							0, 0, 0, 1 };

	//this->_rotationMatrix = rotationMatrix;

	//this->_transformationMatrix = transformation;
	if (j % 60 == 0)
		std::cout << this->_position.x << ", " << this->_position.y << ", " << this->_position.z << std::endl;
	j++;
	glm::vec3 forward = dst - this->_position;

	this->_rotationMatrix = glm::inverse(glm::lookAt(glm::vec3(this->_position), (glm::vec3(dst)), glm::vec3(0, 1, 0)));

	this->_transformationMatrix = this->_translationMatrix * this->_rotationMatrix * this->_scaleMatrix;
}

void HMEngine::Core::Transform::SetPositionAndRotationMatrices(const btTransform& transform)
{
	glm::mat4 tmp;
	transform.getOpenGLMatrix(glm::value_ptr(tmp));

	this->_transformationMatrix = tmp * this->_scaleMatrix;
}

glm::mat4 HMEngine::Core::Transform::GetTranslationMatrix() const
{
	return glm::translate(this->_position);
}

/*
Calculates and returns the model matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetModelMatrix() const
{
	//return this->_translationMatrix * this->_rotationMatrix * this->_scaleMatrix;
	return this->_transformationMatrix;
}

/*
Returns the view matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetViewMatrix() const
{
	return HMEngine::Core::Rendering::Camera::GetInstance().GetViewMatrix();
}

/*
Calculates and returns the MVP matrix.
*/
glm::mat4 HMEngine::Core::Transform::GetMVPMatrix() const
{
	return HMEngine::GameSettings::GetProjectionMatrix() * this->GetViewMatrix() * this->GetModelMatrix();
}

void HMEngine::Core::Transform::UpdateTranslationMatrix()
{
	this->_translationMatrix = glm::translate(this->_position);

	this->_transformationMatrix = this->_translationMatrix * this->_rotationMatrix * this->_scaleMatrix;
}

void HMEngine::Core::Transform::UpdateRotationMatrix()
{
	this->_rotationQuat = glm::quat(this->_rotation);

	this->_rotationMatrix = glm::mat4(this->_rotationQuat);

	this->_transformationMatrix = this->_translationMatrix * this->_rotationMatrix * this->_scaleMatrix;
}

void HMEngine::Core::Transform::UpdateScaleMatrix()
{
	this->_scaleMatrix = glm::scale(this->_scale);

	this->_transformationMatrix = this->_translationMatrix * this->_rotationMatrix * this->_scaleMatrix;
}
