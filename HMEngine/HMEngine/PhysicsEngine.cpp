#include "PhysicsEngine.h"
#include "Ray.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaycastInfo.h"
#include "Collider.h"
#include <set>
#include "bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"

std::unordered_map<HMEngine::Core::Physics::Colliders::Collider*, HMEngine::Core::GameObject*> HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders;
HMEngine::Core::Physics::PhysicsEngine::BulletData HMEngine::Core::Physics::PhysicsEngine::_bulletData;
std::vector<btCollisionShape*> HMEngine::Core::Physics::PhysicsEngine::_collisionShapes;
std::unordered_map<btRigidBody*, HMEngine::Core::GameObject*> HMEngine::Core::Physics::PhysicsEngine::_rigidBodies;

/*
Returns whether the ray is colling with some object.
Input:
origin - Initial position of the ray
direction - direction of the ray
maxDistance - maximum distance of the ray
Output:
True if ray hitting some object, false otherwise.
*/
HMEngine::Core::Physics::RaycastInfo HMEngine::Core::Physics::PhysicsEngine::Raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance)
{
	HMEngine::Core::Physics::Ray ray = HMEngine::Core::Physics::Ray(origin, direction);
	return HMEngine::Core::Physics::PhysicsEngine::Raycast(ray);
}

/*
Returns whether the ray is colliding with some object.
Input:
ray - the ray
maxDistance - maximum distance of the ray
Output:
True if ray hitting some object, false otherwise.
*/
HMEngine::Core::Physics::RaycastInfo HMEngine::Core::Physics::PhysicsEngine::Raycast(const HMEngine::Core::Physics::Ray& ray)
{
	HMEngine::Core::Physics::RaycastInfo info = HMEngine::Core::Physics::RaycastInfo();
	info.ray = ray;

	glm::vec3 rayDirection = ray.GetDirection();
	glm::vec3 rayOrigin = ray.GetOrigin();
	glm::vec3 rayEnd = rayOrigin + rayDirection * 1000.0f;

	btCollisionWorld::ClosestRayResultCallback RayCallback(
		btVector3(rayOrigin.x, rayOrigin.y, rayOrigin.z),
		btVector3(rayEnd.x, rayEnd.y, rayEnd.z)
	);

	HMEngine::Core::Physics::PhysicsEngine::GetBulletData().dynamicsWorld->rayTest(
		btVector3(rayOrigin.x, rayOrigin.y, rayOrigin.z),
		btVector3(rayEnd.x, rayEnd.y, rayEnd.z),
		RayCallback
	);

	if (RayCallback.hasHit())
	{
		auto gameObject = (HMEngine::Core::GameObject*)RayCallback.m_collisionObject->getUserPointer();
		info.hits.emplace(glm::distance(rayOrigin, gameObject->GetTransform().GetPosition()), gameObject);
		info.isHit = true;
	}

	return info;
}

void HMEngine::Core::Physics::PhysicsEngine::AddGameObjectCollider(HMEngine::Core::Physics::Colliders::Collider* collider)
{
	HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders.emplace(collider, &collider->GetParent());
	if (collider->_rigidBody != nullptr)
		HMEngine::Core::Physics::PhysicsEngine::_rigidBodies.emplace(collider->_rigidBody, &collider->GetParent());
}

void HMEngine::Core::Physics::PhysicsEngine::RemoveGameObjectCollider(HMEngine::Core::Physics::Colliders::Collider* collider)
{
	HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders.erase(collider);
	HMEngine::Core::Physics::PhysicsEngine::_rigidBodies.erase(collider->_rigidBody);
}

void HMEngine::Core::Physics::PhysicsEngine::Initialize()
{
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.broadphase = new btDbvtBroadphase();

	// Set up the collision configuration and dispatcher
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.collisionConfiguration = new btDefaultCollisionConfiguration();
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.dispatcher = new btCollisionDispatcher(
		HMEngine::Core::Physics::PhysicsEngine::_bulletData.collisionConfiguration);

	btGImpactCollisionAlgorithm::registerAlgorithm(HMEngine::Core::Physics::PhysicsEngine::_bulletData.dispatcher);

	// The actual physics solver
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.solver = new btSequentialImpulseConstraintSolver;

	// The world.
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.dynamicsWorld = new btDiscreteDynamicsWorld(HMEngine::Core::Physics::PhysicsEngine::_bulletData.dispatcher,
		HMEngine::Core::Physics::PhysicsEngine::_bulletData.broadphase, HMEngine::Core::Physics::PhysicsEngine::_bulletData.solver,
		HMEngine::Core::Physics::PhysicsEngine::_bulletData.collisionConfiguration);
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.dynamicsWorld->setGravity(btVector3(0, -9.81f, 0));
}

void HMEngine::Core::Physics::PhysicsEngine::Destroy()
{
	delete HMEngine::Core::Physics::PhysicsEngine::_bulletData.broadphase;
	delete HMEngine::Core::Physics::PhysicsEngine::_bulletData.collisionConfiguration;
	delete HMEngine::Core::Physics::PhysicsEngine::_bulletData.dispatcher;
	delete HMEngine::Core::Physics::PhysicsEngine::_bulletData.dynamicsWorld;
	delete HMEngine::Core::Physics::PhysicsEngine::_bulletData.solver;

	for (auto& collisionShape : HMEngine::Core::Physics::PhysicsEngine::_collisionShapes)
		delete collisionShape;
}

void HMEngine::Core::Physics::PhysicsEngine::Update()
{
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.dynamicsWorld->stepSimulation(1);
	btTransform trans;

	for (auto& pair : HMEngine::Core::Physics::PhysicsEngine::_rigidBodies)
	{
		trans = pair.first->getWorldTransform();
		btVector3& origin = trans.getOrigin();
		auto& objectTransform = pair.second->GetTransform();

		float originalY = origin.y();
		origin.setY(RoundNumber(origin.y()));
		objectTransform.SetPosition(origin.x(), origin.y(), origin.z());
		objectTransform.SetPositionAndRotationMatrices(trans);
	}

	int numManifolds = HMEngine::Core::Physics::PhysicsEngine::_bulletData.dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = HMEngine::Core::Physics::PhysicsEngine::_bulletData.dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();

		auto a = ((HMEngine::Core::GameObject*)(obA->getUserPointer()));
		auto b = ((HMEngine::Core::GameObject*)(obB->getUserPointer()));

		for (auto& e : a->_collideEvent)
			e(a, b);
		for (auto& e : b->_collideEvent)
			e(b, a);
	}
}

/*
Rounds a number properly.
for example: 98.658 -> 98.7
*/
float HMEngine::Core::Physics::PhysicsEngine::RoundNumber(float x)
{
	float decimal = abs(x - int(x));
	unsigned int number = abs(int(x));
	int firstDigit = int(decimal * 10);
	int secondDigit = int(decimal * 100) - firstDigit * 10;
	int thirdDigit = int(decimal * 1000) - secondDigit * 10 - firstDigit * 100;
	//if (thirdDigit >= 5.0f)
	//{
	//	//round up
	//	secondDigit++;
	//	thirdDigit = 0;
	//	if (secondDigit >= 10.0f)
	//	{
	//		firstDigit++;
	//		if (firstDigit >= 10.0f)
	//		{
	//			firstDigit = 0;
	//			number++;
	//		}
	//	}
	//}
	if (secondDigit >= 7)
	{
		firstDigit++;
		if (firstDigit >= 10)
		{
			number++;
			firstDigit = 0;
		}
	}
	secondDigit = 0;
	int factor = x > 0.0f ? 1 : -1;

	return (number + (firstDigit / 10.0f) + (secondDigit / 100.0f)) * factor;
}
