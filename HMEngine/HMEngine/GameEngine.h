#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core::Rendering
	{
		class Window;
	}
	class GameEngine
	{
	public:
		static float zNear;
		static float zFar;
		static float FovInDegrees;
		static unsigned int windowWidth;
		static unsigned int windowHeight;

		GameEngine();
		~GameEngine();

		void CreateNewWindow(int width, int height, const std::string& title, bool fullscreen);
		inline void SetFov(float fovInDegrees) { HMEngine::GameEngine::FovInDegrees = fovInDegrees; }
		void Run();

	private:
		HMEngine::Core::Rendering::Window* _window;
	};
}