#pragma once
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\matrix_transform_2d.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

namespace HMEngine
{
	class GameEngine;

	class GameSettings
	{
		friend class GameEngine;
	public:
		GameSettings() = delete;
		~GameSettings() = delete;

		static const glm::vec3& X_AXIS;
		static const glm::vec3& Y_AXIS;
		static const glm::vec3& Z_AXIS;

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