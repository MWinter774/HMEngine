#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	class GameEngine;

	class GameSettings
	{
		friend class GameEngine;
	public:
		GameSettings() = delete;
		~GameSettings() = delete;

		static float GetFov() { return HMEngine::GameSettings::fovInDegrees; }
		static unsigned int GetWindowWidth() { return HMEngine::GameSettings::windowWidth; }
		static unsigned int GetWindowHeight() { return HMEngine::GameSettings::windowHeight; }
		static float GetZNear() { return HMEngine::GameSettings::zNear; }
		static float GetZFar() { return HMEngine::GameSettings::zFar; }

		static void SetFov(float fovInDegrees);
		static void SetZNear(float zNear);
		static void SetZFar(float zFar);

		static glm::mat4 GetProjectionMatrix();
	private:
		static void UpdateProjectionMatrix();

		static float zNear;
		static float zFar;
		static float fovInDegrees;
		static unsigned int windowWidth;
		static unsigned int windowHeight;
		static glm::mat4 projectionMatrix;
	};
}