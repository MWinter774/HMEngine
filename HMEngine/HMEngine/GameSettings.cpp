#include "GameSettings.h"
#include "AmbientLightShader.h"
#include "TerrainShader.h"

float HMEngine::GameSettings::zNear = 0.1f;
float HMEngine::GameSettings::zFar = 1000.0f;
float HMEngine::GameSettings::fovInDegrees = 60.0f;
unsigned int HMEngine::GameSettings::windowWidth = 800;
unsigned int HMEngine::GameSettings::windowHeight = 600;
glm::mat4 HMEngine::GameSettings::projectionMatrix = glm::perspective(glm::radians(HMEngine::GameSettings::fovInDegrees), HMEngine::GameSettings::windowWidth / (float)HMEngine::GameSettings::windowHeight, HMEngine::GameSettings::zNear, HMEngine::GameSettings::zFar);
glm::vec3 HMEngine::GameSettings::ambientLight = glm::vec3(0.15f, 0.15f, 0.15f);
const glm::vec3& HMEngine::GameSettings::X_AXIS = glm::vec3(1.0, 0.0, 0.0);
const glm::vec3& HMEngine::GameSettings::Y_AXIS = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3& HMEngine::GameSettings::Z_AXIS = glm::vec3(0.0, 0.0, 1.0);
bool HMEngine::GameSettings::isCursorLocked = true;
bool HMEngine::GameSettings::isCursorVisible = false;
float HMEngine::GameSettings::sensitivity = 0.003f;
bool HMEngine::GameSettings::calculateFPS = false;
float HMEngine::GameSettings::fogDensity = 0.0035f;
float HMEngine::GameSettings::fogGradient = 5.0f;
glm::vec3 HMEngine::GameSettings::skyColor = glm::vec3(0.6f, 0.8f, 1.0f);

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

void HMEngine::GameSettings::SetAmbientLight(const glm::vec3& ambientLight)
{
	HMEngine::GameSettings::ambientLight = ambientLight;
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().Bind();
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().UpdateAmbientLight();
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().Bind();
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().UpdateAmbientLight();
}

void HMEngine::GameSettings::SetFogDensity(float fogDensity)
{
	HMEngine::GameSettings::fogDensity = fogDensity;
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().Bind();
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().UpdateFogDensity();
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().Bind();
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().UpdateFogDensity();
}

void HMEngine::GameSettings::SetFogGradient(float fogGradient)
{
	HMEngine::GameSettings::fogGradient = fogGradient;
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().Bind();
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().UpdateFogGradient();
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().Bind();
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().UpdateFogGradient();
}

void HMEngine::GameSettings::SetSkyColor(const glm::vec3 & skyColor)
{
	HMEngine::GameSettings::skyColor = skyColor;
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().Bind();
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().UpdateSkyColor();
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().Bind();
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().UpdateSkyColor();
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