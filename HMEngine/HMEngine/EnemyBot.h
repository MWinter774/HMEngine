#pragma once
#include "GameObject.h"
#include <string>
#include "glm\glm.hpp"
#include "EventObject.h"

namespace HMEngine
{
	class PhysicalPlayer;
	namespace Components
	{
		class MeshRenderer;
		class BrainComponent;
	}
	namespace Core
	{
		namespace Physics
		{
			namespace Colliders
			{
				class BoundingSphere;
			}
		}
	}
	namespace UI
	{
		class Billboard;
		class ProgressBar;
	}
}

class EnemyBot : public HMEngine::Core::GameObject, public HMEngine::Core::EventObject
{
public:
	EnemyBot(const std::string& name, const glm::vec3& position, HMEngine::PhysicalPlayer* player);
	~EnemyBot();

	inline HMEngine::Core::GameObject* Clone() const override { return new EnemyBot(*this); }

	void UpdateEvent() override;

	void AttachToGameEngineEvent() override;

private:
	HMEngine::Components::MeshRenderer* _mesh;
	HMEngine::Components::BrainComponent* _brain;
	HMEngine::Core::Physics::Colliders::BoundingSphere* _collider;
	HMEngine::PhysicalPlayer* _player;
	HMEngine::UI::ProgressBar* _health;
	HMEngine::UI::Billboard* _healthBar;
};

