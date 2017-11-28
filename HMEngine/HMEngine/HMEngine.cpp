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
	}
}