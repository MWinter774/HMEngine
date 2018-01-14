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
		Player(const std::string& playerName);
		~Player();
		Player(const HMEngine::Player& other);
		HMEngine::Player& operator=(const HMEngine::Player& other);

	private:
		HMEngine::Components::MeshRenderer* _meshRenderer;
		HMEngine::Components::CameraController* _cameraController;
	};
}