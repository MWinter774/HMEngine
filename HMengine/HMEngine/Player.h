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
	private:
		HMEngine::Components::MeshRenderer* _meshRenderer;
		HMEngine::Components::CameraController* _cameraController;
	};
}