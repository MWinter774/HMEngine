#include "PhysicsEngine.h"
#include "Ray.h"
#include "BoundingSphere.h"
#include "GameObject.h"
#include "Transform.h"
#include "RaycastInfo.h"

std::unordered_set<HMEngine::Core::Physics::Colliders::Collider*> HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders;
HMEngine::Core::Physics::PhysicsEngine::BulletData HMEngine::Core::Physics::PhysicsEngine::_bulletData;

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
	glm::vec3 rayEnd = rayOrigin + rayDirection * 100.0f;

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
		std::cout << "Hit!" << std::endl;
	}
	else 
	{
		std::cout << "Not Hit!" << std::endl;
	}

	//float b = 0.0f;
	//float c = 0.0f;
	//glm::vec3 center;
	//float radius = 0.0f;
	//glm::vec3 distance;
	//HMEngine::Core::Physics::Colliders::Collider* boundingSphere = nullptr;
	//for (auto item : HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders)
	//{
	//	/*boundingSphere = item.first;
	//	radius = boundingSphere->GetRadius();
	//	center = boundingSphere->GetCenter() + item.second->GetTransform().GetPosition();
	//	distance = rayOrigin - center;

	//	b = glm::dot(rayDirection, distance);
	//	c = glm::dot(distance, distance) - radius * radius;
	//	if (b * b - c >= 0)
	//	{
	//		info.isHit = true;
	//		info.hits.emplace(glm::distance(rayOrigin, center), item.second);
	//	}*/
	//}


	return info;
}

void HMEngine::Core::Physics::PhysicsEngine::AddGameObjectCollider(HMEngine::Core::Physics::Colliders::Collider* collider)
{
	HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders.insert(collider);
}

void HMEngine::Core::Physics::PhysicsEngine::RemoveGameObjectCollider(HMEngine::Core::Physics::Colliders::Collider* collider)
{
	HMEngine::Core::Physics::PhysicsEngine::_gameObjectColliders.erase(collider);
}

void HMEngine::Core::Physics::PhysicsEngine::Initialize()
{
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.broadphase = new btDbvtBroadphase();

	// Set up the collision configuration and dispatcher
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.collisionConfiguration = new btDefaultCollisionConfiguration();
	HMEngine::Core::Physics::PhysicsEngine::_bulletData.dispatcher = new btCollisionDispatcher(
		HMEngine::Core::Physics::PhysicsEngine::_bulletData.collisionConfiguration);

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
}
