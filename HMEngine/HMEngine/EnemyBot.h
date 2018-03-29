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
	EnemyBot(const std::string& name, const glm::vec3& position, HMEngine::PhysicalPlayer* player, const std::string& gnnFilePath = "");
	~EnemyBot();

	inline HMEngine::Core::GameObject* Clone() const override { return new EnemyBot(*this); }

	void UpdateEvent() override;

	void AttachToGameEngineEvent() override;

	bool GotHit(float damageInPercentage);

	void SetPosition(const glm::vec3& position);
	void AddPosition(const glm::vec3& translation);
	void SetHealth(float health);

	bool Shoot();

	void Lost();

private:
	enum term { A = 0, B, C, D };
	static bool IsObjectVisible(const glm::mat4& objectMVPMatrix, const glm::vec3& objectPos, float radius);

	std::string _gnnFilePath;
	HMEngine::Components::MeshRenderer* _mesh;
	HMEngine::Components::BrainComponent* _brain;
	HMEngine::Core::Physics::Colliders::BoundingSphere* _collider;
	HMEngine::PhysicalPlayer* _player;
	HMEngine::UI::ProgressBar* _health;
	HMEngine::UI::Billboard* _healthBar;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	glm::vec3 _forward;
};

