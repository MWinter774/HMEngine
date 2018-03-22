#include "Collider.h"
#include "PhysicsEngine.h"
#include "GameObject.h"

HMEngine::Core::Physics::Colliders::Collider::Collider()
{
}

HMEngine::Core::Physics::Colliders::Collider::~Collider()
{
	HMEngine::Core::Physics::PhysicsEngine::RemoveGameObjectCollider(this);
}

void HMEngine::Core::Physics::Colliders::Collider::AttachToGameObjectEvent()
{
	if (this->_parentObject->GetMeshRenderer() != nullptr)
	{
		this->Initialize();
		HMEngine::Core::Physics::PhysicsEngine::AddGameObjectCollider(this);
	}
}