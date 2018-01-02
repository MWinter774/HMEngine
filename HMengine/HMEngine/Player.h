#pragma once
#include "GameObject.h"

namespace HMEngine
{
	namespace Core
	{
		class GameObject;
	}

	class Player : public HMEngine::Core::GameObject
	{
	public:
		Player();
		~Player();
	private:
		HMEngine::Core::GameObject* go;
	};
}