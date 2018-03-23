#include "Collider.h"
#include "PhysicsEngine.h"
#include "GameObject.h"

HMEngine::Core::Physics::Colliders::Collider::Collider() : _collider(nullptr), _rigidBody(nullptr)
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
	if (this->_parentObject->GetMeshRenderer() != nullptr)
	{
		this->Initialize();
		HMEngine::Core::Physics::PhysicsEngine::AddGameObjectCollider(this);
		if (this->_collider != nullptr)
			HMEngine::Core::Physics::PhysicsEngine::AddCollisionShape(this->_collider);
	}
}