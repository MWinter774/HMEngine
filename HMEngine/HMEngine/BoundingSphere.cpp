#include "BoundingSphere.h"
#include "bullet\btBulletDynamicsCommon.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "PhysicsEngine.h"
#include "glm\gtc\quaternion.hpp"
#include "Transform.h"

HMEngine::Core::Physics::Colliders::BoundingSphere::BoundingSphere(float mass) : HMEngine::Core::Physics::Colliders::Collider(mass), _center(-999, -999, -999), _radius(-1)
{
}

HMEngine::Core::Physics::Colliders::BoundingSphere::BoundingSphere(float mass, const glm::vec3& center, float radius) : HMEngine::Core::Physics::Colliders::Collider(mass), _center(center), _radius(radius)
{
}

HMEngine::Core::Physics::Colliders::BoundingSphere::~BoundingSphere()
{
}

void HMEngine::Core::Physics::Colliders::BoundingSphere::Initialize()
{
	if (this->_center == glm::vec3(-999, -999, -999) || this->_radius == -1)
	{
		this->_center = this->_parentObject->GetMeshRenderer()->GetCenter();
		this->_radius = this->_parentObject->GetMeshRenderer()->GetRadius();
	}
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
