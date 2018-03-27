#pragma once

namespace HMEngine
{
	class Timer
	{
	public:
		static double GetTime();
		inline static double GetDelta() { return HMEngine::Timer::_delta; }
		inline static void SetDelta(double delta) { HMEngine::Timer::_delta = delta; }

	private:
		Timer() = delete;
		~Timer() = delete;

		static double _freq;
		static bool _timerInitialized;
		static double _delta;
	};
}