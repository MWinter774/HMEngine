#include "Collider.h"
#include "PhysicsEngine.h"
#include "GameObject.h"

HMEngine::Core::Physics::Colliders::Collider::Collider(float mass) : _collider(nullptr), _rigidBody(nullptr), _mass(abs(mass))
{
}

HMEngine::Core::Physics::Colliders::Collider::~Collider()
{
	HMEngine::Core::Physics::PhysicsEngine::RemoveGameObjectCollider(this);

	if (this->_rigidBody != nullptr)
	{
		HMEngine::Core::Physics::PhysicsEngine::GetBulletData().dynamicsWorld->removeRigidBody(this->_rigidBody);
		delete this->_rigidBody->getMotionState();
		delete this->_rigidBody;
	}
}

void HMEngine::Core::Physics::Colliders::Collider::AttachToGameObjectEvent()
{
	this->Initialize();
	HMEngine::Core::Physics::PhysicsEngine::AddGameObjectCollider(this);
	if (this->_collider != nullptr)
		HMEngine::Core::Physics::PhysicsEngine::AddCollisionShape(this->_collider);
}

void HMEngine::Core::Physics::Colliders::Collider::ApplyForce(const glm::vec3& force)
{
	this->_rigidBody->applyCentralForce(btVector3(force.x, force.y, force.z));
	if (force.y == 0)
	{
		this->_rigidBody->setLinearVelocity(btVector3(0, -9.81f, 0));
		this->_rigidBody->setAngularVelocity(btVector3(0, -9.81f, 0));
	}
	else
	{
		this->_rigidBody->setLinearVelocity(btVector3(0, force.y, 0));
		this->_rigidBody->setAngularVelocity(btVector3(0, force.y, 0));
	}
}