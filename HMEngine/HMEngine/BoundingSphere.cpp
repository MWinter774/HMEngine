#include "BoundingSphere.h"
#include "IntersectionData.h"
#include "bullet\btBulletDynamicsCommon.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "PhysicsEngine.h"
#include "glm\gtc\quaternion.hpp"
#include "Transform.h"

HMEngine::Core::Physics::Colliders::BoundingSphere::BoundingSphere() : _collider(nullptr)
{
}

HMEngine::Core::Physics::Colliders::BoundingSphere::BoundingSphere(const glm::vec3& center, float radius) : _center(center), _radius(radius), _collider(nullptr)
{
}

HMEngine::Core::Physics::Colliders::BoundingSphere::~BoundingSphere()
{
	if (this->_collider != nullptr)
	{
		delete this->_collider;
		HMEngine::Core::Physics::PhysicsEngine::GetBulletData().dynamicsWorld->removeRigidBody(this->_rigidBody);
		delete this->_rigidBody->getMotionState();
		delete this->_rigidBody;
	}
}

HMEngine::Core::Physics::Colliders::BoundingSphere::BoundingSphere(const HMEngine::Core::Physics::Colliders::BoundingSphere& other) :
	_radius(other._radius), _center(other._center)
{
	if (other._collider != nullptr)
		this->_collider = new btSphereShape(*other._collider);
}

HMEngine::Core::Physics::Colliders::BoundingSphere& HMEngine::Core::Physics::Colliders::BoundingSphere::operator=(
	const HMEngine::Core::Physics::Colliders::BoundingSphere& other)
{
	if (this != &other)
	{
		if (this->_collider != nullptr)
			delete this->_collider;

		this->_radius = other._radius;
		this->_center = other._center;

		if (other._collider != nullptr)
			this->_collider = new btSphereShape(*other._collider);
	}

	return *this;
}

HMEngine::Core::Physics::IntersectionData HMEngine::Core::Physics::Colliders::BoundingSphere::IsIntersect(const HMEngine::Core::Physics::Colliders::BoundingSphere& other)
{
	float radiusDistance = this->_radius + other._radius; //distance between centers if the spheres are touching
	float centerDistance = float((other._center - this->_center).length()); //distance between sphere's centers

	return HMEngine::Core::Physics::IntersectionData(centerDistance < radiusDistance, centerDistance - radiusDistance);
}

void HMEngine::Core::Physics::Colliders::BoundingSphere::Initialize()
{
	this->_center = this->_parentObject->GetMeshRenderer()->GetCenter();
	this->_radius = this->_parentObject->GetMeshRenderer()->GetRadius();
	this->_collider = new btSphereShape(this->_radius);

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
