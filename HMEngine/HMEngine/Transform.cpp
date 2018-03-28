#include "Transform.h"
#include "Camera.h"
#include "GameSettings.h"
#include "GL\glew.h"
#include <iostream>
#include "glm\gtx\norm.hpp"
#include "glm\gtx\quaternion.hpp"
#include "glm\gtx\normal.hpp"

HMEngine::Core::Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : _position(position), _rotation(rotation), _scale(scale)
{
	this->UpdateTranslationMatrix();
	this->UpdateRotationMatrix();
	this->UpdateScaleMatrix();
}

HMEngine::Core::Transform::~Transform()
{
}

void HMEngine::Core::Transform::LookAt(const glm::vec3& dst)
{
	glm::vec3 direction = dst - this->_position;

	glm::quat rot1 = HMEngine::Core::Transform::RotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), direction);

	glm::vec3 desiredUp = glm::vec3(0, 1, 0);

	glm::vec3 newUp = rot1 * glm::vec3(0.0f, 1.0f, 0.0f);
	glm::quat rot2 = HMEngine::Core::Transform::RotationBetweenVectors(newUp, desiredUp);

	glm::quat targetOrientation = rot2 * rot1;

	this->_rotationQuat = targetOrientation;

	this->_rotationMatrix = glm::toMat4(this->_rotationQuat);
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

glm::quat HMEngine::Core::Transform::RotationBetweenVectors(const glm::vec3& start_, const glm::vec3& dest_)
{
	glm::vec3 start = glm::normalize(start_);
	glm::vec3 dest = glm::normalize(dest_ + glm::vec3(0.01f, 0, 0.01f));

	float cosTheta = glm::dot(start, dest);
	glm::vec3 rotationAxis;
	if (cosTheta < -1 + 0.001f)
	{
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (glm::length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return glm::angleAxis(glm::radians(180.0f), rotationAxis);
	}

	rotationAxis = cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

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
