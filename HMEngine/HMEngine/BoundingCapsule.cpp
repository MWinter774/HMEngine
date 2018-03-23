#include "BoundingCapsule.h"
#include "GameObject.h"
#include "Transform.h"
#include "PhysicsEngine.h"
#include "MeshRenderer.h"

HMEngine::Core::Physics::Colliders::BoundingCapsule::BoundingCapsule(float mass) : HMEngine::Core::Physics::Colliders::Collider(mass)
{
}

HMEngine::Core::Physics::Colliders::BoundingCapsule::~BoundingCapsule()
{
}

void HMEngine::Core::Physics::Colliders::BoundingCapsule::Initialize()
{
	float radius = this->_parentObject->GetMeshRenderer()->GetRadius();
	float height = 0.0f;
	float minY = 999.0f, maxY = -999.0f;

	for (auto& vertex : this->_parentObject->GetMeshRenderer()->GetVertices())
	{
		if (vertex.y > maxY) maxY = vertex.y;
		if (vertex.y < minY) minY = vertex.y;
	}

	height = abs(maxY - minY) * this->_parentObject->GetTransform().GetScaleY();
	radius = (abs(radius - height) / 2.0f) * this->_parentObject->GetTransform().GetScaleX();
	this->_collider = new btCapsuleShape(radius, height);

	glm::quat rotationQuat = this->_parentObject->GetTransform().GetRotationQuat();
	glm::vec3 position = this->_parentObject->GetTransform().GetPosition();

	btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(
		btQuaternion(rotationQuat.x, rotationQuat.y, rotationQuat.z, rotationQuat.w),
		btVector3(position.x, position.y, position.z)
	));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		this->_mass,                  // mass, in kg. 0 -> Static object, will never move.
		motionState,
		this->_collider,  // collision shape of body
		btVector3(0, 0, 0)    // local inertia
	);

	this->_rigidBody = new btRigidBody(rigidBodyCI);
	this->_rigidBody->setUserPointer(this);

	HMEngine::Core::Physics::PhysicsEngine::GetBulletData().dynamicsWorld->addRigidBody(this->_rigidBody);
}