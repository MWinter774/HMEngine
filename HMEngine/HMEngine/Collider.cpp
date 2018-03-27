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
	/*this->_rigidBody->applyGravity();
	auto pos = this->_rigidBody->getWorldTransform().getOrigin();
	auto k = pos + btVector3(translation.x, translation.y, translation.z);
	this->_rigidBody->getWorldTransform().getOrigin().setX(pos.x() + translation.x);*/

	if (translation.x + translation.y + translation.z != 0)
	{
		this->_rigidBody->applyGravity();
		btTransform initialTransform;
		auto pos = this->_rigidBody->getWorldTransform().getOrigin();
		//auto k = btVector3(pos.x, pos.y, pos.z) + btVector3(translation.x, translation.y, translation.z);
		auto k = pos + btVector3(translation.x, translation.y, translation.z);

		initialTransform.setOrigin(k);
		initialTransform.setRotation(this->_rigidBody->getOrientation());

		this->_rigidBody->setWorldTransform(initialTransform);
		//this->_rigidBody->getMotionState()->setWorldTransform(initialTransform);
		//this->_rigidBody->setLinearVelocity(btVector3(0.0f, -9.81f, 0.0f));

		//btTransform tr;
		//this->_rigidBody->getMotionState()->getWorldTransform(tr);
		//auto k = tr.getOrigin() + btVector3(translation.x, translation.y, translation.z);
		//tr.setOrigin(k);
		//this->_rigidBody->getMotionState()->setWorldTransform(tr);
		//this->_parentObject->GetTransform().SetPosition(k.x(),k.y(),k.z());
	}
}