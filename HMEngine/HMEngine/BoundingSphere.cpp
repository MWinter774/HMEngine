#include "BoundingSphere.h"
#include "bullet\btBulletDynamicsCommon.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "PhysicsEngine.h"
#include "glm\gtc\quaternion.hpp"
#include "Transform.h"

HMEngine::Core::Physics::Colliders::BoundingSphere::BoundingSphere(float mass) : HMEngine::Core::Physics::Colliders::Collider(mass)
{
}

HMEngine::Core::Physics::Colliders::BoundingSphere::~BoundingSphere()
{
}

void HMEngine::Core::Physics::Colliders::BoundingSphere::Initialize()
{
	this->_center = this->_parentObject->GetMeshRenderer()->GetCenter();
	this->_radius = this->_parentObject->GetMeshRenderer()->GetRadius();
	this->_collider = new btSphereShape(this->_radius * this->_parentObject->GetTransform().GetScaleX());

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
		btVector3(this->_center.x, this->_center.y, this->_center.z)    // local inertia
	);

	this->_rigidBody = new btRigidBody(rigidBodyCI);
	this->_rigidBody->setUserPointer(this);

	HMEngine::Core::Physics::PhysicsEngine::GetBulletData().dynamicsWorld->addRigidBody(this->_rigidBody);
}
