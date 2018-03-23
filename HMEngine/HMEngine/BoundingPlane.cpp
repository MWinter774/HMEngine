#include "BoundingPlane.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "PhysicsEngine.h"

HMEngine::Core::Physics::Colliders::BoundingPlane::BoundingPlane::BoundingPlane()
{
}

HMEngine::Core::Physics::Colliders::BoundingPlane::BoundingPlane::~BoundingPlane()
{
}

void HMEngine::Core::Physics::Colliders::BoundingPlane::Initialize()
{
	glm::vec3 minVertex = this->_parentObject->GetTransform().GetPosition(), maxVertex = this->_parentObject->GetTransform().GetPosition();

	for (auto& vertex : this->_parentObject->GetMeshRenderer()->GetVertices())
	{
		if (vertex.x > maxVertex.x)	maxVertex.x = vertex.x;
		if (vertex.y > maxVertex.y)	maxVertex.y = vertex.y;
		if (vertex.z > maxVertex.z)	maxVertex.z = vertex.z;

		if (vertex.x < minVertex.x)	minVertex.x = vertex.x;
		if (vertex.y < minVertex.y)	minVertex.y = vertex.y;
		if (vertex.z < minVertex.z)	minVertex.z = vertex.z;
	}

	float width = abs(maxVertex.x - minVertex.x);
	float height = abs(maxVertex.y - minVertex.y);
	float depth = abs(maxVertex.z - minVertex.z);

	this->_collider = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));

	glm::quat rotationQuat = this->_parentObject->GetTransform().GetRotationQuat();
	glm::vec3 position = this->_parentObject->GetTransform().GetPosition();

	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(
		btQuaternion(rotationQuat.x, rotationQuat.y, rotationQuat.z, rotationQuat.w),
		btVector3(position.x, position.y, position.z)
	));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		0,                  // mass, in kg. 0 -> Static object, will never move.
		motionState,
		this->_collider,  // collision shape of body
		btVector3(0, 0, 0)    // local inertia
	);

	this->_rigidBody = new btRigidBody(rigidBodyCI);
	this->_rigidBody->setUserPointer(this);

	HMEngine::Core::Physics::PhysicsEngine::GetBulletData().dynamicsWorld->addRigidBody(this->_rigidBody);
}