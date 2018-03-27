#include "Timer.h"
#include <time.h>
#include <Windows.h>
#include <iostream>

double HMEngine::Timer::_freq = 0.0;
bool HMEngine::Timer::_timerInitialized = false;
double HMEngine::Timer::_delta = 0.0f;

double HMEngine::Timer::GetTime()
{
	if (!HMEngine::Timer::_timerInitialized)
	{
		LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			std::cerr << "QueryPerformanceFrequency failed in timer initialization" << std::endl;

		HMEngine::Timer::_freq = double(li.QuadPart);
		HMEngine::Timer::_timerInitialized = true;
	}

	LARGE_INTEGER li;
	if (!QueryPerformanceCounter(&li))
		std::cerr << "QueryPerformanceCounter failed in get time!" << std::endl;

	return double(li.QuadPart) / HMEngine::Timer::_freq;
}
