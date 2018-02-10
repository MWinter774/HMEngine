#pragma once
#include <string>
#include "GameObject.h"

namespace HMEngine
{
	namespace Components
	{
		class MeshRenderer;
		class CameraController;
	}
	class Player : public HMEngine::Core::GameObject
	{
	public:
		Player(const std::string& playerName, float walkingSpeed = 3.0f, float runningSpeed = 10.0f);
		~Player();
		Player(const HMEngine::Player& other);
		HMEngine::Player& operator=(const HMEngine::Player& other);

		inline HMEngine::Core::GameObject* Clone() const override { return new HMEngine::Player(*this); }

	private:
		HMEngine::Components::MeshRenderer* _meshRenderer;
		HMEngine::Components::CameraController* _cameraController;
	};
}