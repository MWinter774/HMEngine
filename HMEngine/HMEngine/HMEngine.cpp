#include "HMEngine.h"

HMEngine::GameEngine::GameEngine()
{
}

HMEngine::GameEngine::~GameEngine()
{
}

void HMEngine::GameEngine::Run()
{
	int numOfTime = ~0;
	while (true) //temp
	{
		HMEngine::Core::Hardware::HardwareInputs::Update();
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(HMEngine::Keys::KEY_W))
			std::cout << "Thats pretty good" << std::endl;
		numOfTime--;
	}
}