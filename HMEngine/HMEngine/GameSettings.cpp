#include "GameSettings.h"

float HMEngine::GameSettings::zNear = 0.1f;
float HMEngine::GameSettings::zFar = 100.0f;
float HMEngine::GameSettings::fovInDegrees = 60.0f;
unsigned int HMEngine::GameSettings::windowWidth = 800.0f;
unsigned int HMEngine::GameSettings::windowHeight = 600.0f;
glm::mat4 HMEngine::GameSettings::projectionMatrix = glm::perspective(glm::radians(HMEngine::GameSettings::fovInDegrees), HMEngine::GameSettings::windowWidth / (float)HMEngine::GameSettings::windowHeight, HMEngine::GameSettings::zNear, HMEngine::GameSettings::zFar);
glm::vec3 HMEngine::GameSettings::ambientLight = glm::vec3(0, 0, 0);

/*
Sets the fov of the game and updates the projection matrix so the change will occur in game.
Input:
fovInDegrees - the wanted fov in degrees
*/
void HMEngine::GameSettings::SetFov(float fovInDegrees)
{
	HMEngine::GameSettings::fovInDegrees = fovInDegrees;
	HMEngine::GameSettings::UpdateProjectionMatrix();
}

/*
Sets zNear of the game and updates the projection matrix so the change will occur in game.
Input:
zNear - the wanted fov in degrees
*/
void HMEngine::GameSettings::SetZNear(float zNear)
{
	HMEngine::GameSettings::zNear = zNear;
	HMEngine::GameSettings::UpdateProjectionMatrix();
}

/*
Sets zFar of the game and updates the projection matrix so the change will occur in game.
Input:
zFar - the wanted fov in degrees
*/
void HMEngine::GameSettings::SetZFar(float zFar)
{
	HMEngine::GameSettings::zFar = zFar;
	HMEngine::GameSettings::UpdateProjectionMatrix();
}

/*
Updates the projection matrix.
*/
void HMEngine::GameSettings::UpdateProjectionMatrix()
{
	HMEngine::GameSettings::projectionMatrix = glm::perspective(glm::radians(HMEngine::GameSettings::fovInDegrees), float(HMEngine::GameSettings::windowWidth) / float(HMEngine::GameSettings::windowHeight), HMEngine::GameSettings::zNear, HMEngine::GameSettings::zFar);
}

/*
Returns the projection matrix(used for drawing the objects)
*/
glm::mat4& HMEngine::GameSettings::GetProjectionMatrix()
{
	return HMEngine::GameSettings::projectionMatrix;
}