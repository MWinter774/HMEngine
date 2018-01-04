#pragma once
#include <SDL2.0.7\SDL.h>
#undef main
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
		GameSettings(const HMEngine::GameSettings& other) = delete;
		HMEngine::GameSettings& operator=(const HMEngine::GameSettings& other) = delete;
		~GameSettings() = delete;

		static const glm::vec3& X_AXIS;
		static const glm::vec3& Y_AXIS;
		static const glm::vec3& Z_AXIS;

		static inline float GetFov() { return HMEngine::GameSettings::fovInDegrees; }
		static inline unsigned int GetWindowWidth() { return HMEngine::GameSettings::windowWidth; }
		static inline unsigned int GetWindowHeight() { return HMEngine::GameSettings::windowHeight; }
		static inline float GetZNear() { return HMEngine::GameSettings::zNear; }
		static inline float GetZFar() { return HMEngine::GameSettings::zFar; }
		static inline bool IsCursorLocked() { return HMEngine::GameSettings::isCursorLocked; }
		static inline bool IsCursorVisible() { return HMEngine::GameSettings::isCursorVisible; }
		static inline float GetSensitivity() { return HMEngine::GameSettings::sensitivity; }
		static inline glm::vec3& GetAmbientLight() { return HMEngine::GameSettings::ambientLight; }

		static inline void SetFov(float fovInDegrees);
		static inline void SetZNear(float zNear);
		static inline void SetZFar(float zFar);
		static inline void SetIsCursorLocked(bool isCursorLocked) { HMEngine::GameSettings::isCursorLocked = isCursorLocked; }
		static inline void SetCursorVisible(bool isCursorVisible) { SDL_ShowCursor(isCursorVisible); HMEngine::GameSettings::isCursorVisible = isCursorVisible; }
		static inline void SetSensitivity(float sensitivity) { HMEngine::GameSettings::sensitivity = sensitivity; }

		static glm::mat4& GetProjectionMatrix();
	private:
		static void UpdateProjectionMatrix();

		static float zNear;
		static float zFar;
		static float fovInDegrees;
		static unsigned int windowWidth;
		static unsigned int windowHeight;
		static glm::mat4 projectionMatrix;
		static glm::vec3 ambientLight;
		static bool isCursorLocked;
		static bool isCursorVisible;
		static float sensitivity;
	};
}