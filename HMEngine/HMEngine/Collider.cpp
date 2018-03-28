#include "Collider.h"
#include "PhysicsEngine.h"
#include "GameObject.h"
#include "Transform.h"

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
		this->_rigidBody->setLinearVelocity(btVector3(0.0f, -9.81f, 0.0f));
		//this->_rigidBody->setAngularVelocity(btVector3(0, 0.2f, 0));
	}
	else
	{
		this->_rigidBody->setLinearVelocity(btVector3(0, force.y, 0));
		//this->_rigidBody->setAngularVelocity(btVector3(0, force.y, 0));
	}
}

void HMEngine::Core::Physics::Colliders::Collider::AddPosition(const glm::vec3& translation)
{
	if (translation.x + translation.y + translation.z != 0)
	{
		this->_rigidBody->applyGravity();
		btTransform initialTransform;
		auto pos = this->_rigidBody->getWorldTransform().getOrigin();
		auto k = pos + btVector3(translation.x, translation.y, translation.z);

		initialTransform.setOrigin(k);
		initialTransform.setRotation(this->_rigidBody->getOrientation());

		this->_rigidBody->setWorldTransform(initialTransform);
	}
}

void HMEngine::Core::Physics::Colliders::Collider::SetPosition(const glm::vec3& newPosition)
{
	this->_rigidBody->applyGravity();
	btTransform initialTransform;
	auto k = btVector3(newPosition.x, newPosition.y, newPosition.z);

	initialTransform.setOrigin(k);
	initialTransform.setRotation(this->_rigidBody->getOrientation());

	this->_rigidBody->setWorldTransform(initialTransform);
}

void HMEngine::Core::Physics::Colliders::Collider::SetRotation(const glm::quat& rotation)
{
	this->_rigidBody->applyGravity();
	this->_rigidBody->getWorldTransform().setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));
}
