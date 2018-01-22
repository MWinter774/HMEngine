#include "AmbientLightShader.h"
#include "Transform.h"
#include "GameEngine.h"

void HMEngine::Core::Rendering::Shaders::AmbientLightShader::UpdateUniforms(const HMEngine::Core::Transform & transform)
{
	this->SetUniform("transformationMatrix", transform.GetModelMatrix());
	this->SetUniform("viewMatrix", transform.GetViewMatrix());
	this->SetUniform("projectionMatrix", HMEngine::GameSettings::GetProjectionMatrix());
}

void HMEngine::Core::Rendering::Shaders::AmbientLightShader::UpdateAmbientLight()
{
	this->SetUniform("ambientLight", HMEngine::GameSettings::GetAmbientLight());
}

void HMEngine::Core::Rendering::Shaders::AmbientLightShader::UpdateFogDensity()
{
	this->SetUniform("fogDensity", HMEngine::GameSettings::GetFogDensity());
}

void HMEngine::Core::Rendering::Shaders::AmbientLightShader::UpdateFogGradient()
{
	this->SetUniform("fogGradient", HMEngine::GameSettings::GetFogGradient());
}

void HMEngine::Core::Rendering::Shaders::AmbientLightShader::UpdateSkyColor()
{
	this->SetUniform("skyColor", HMEngine::GameSettings::GetSkyColor());
}

HMEngine::Core::Rendering::Shaders::AmbientLightShader::AmbientLightShader()
{
	std::string vs = "./resources/shaders/ambientLightShader.vs";
	std::string fs = "./resources/shaders/ambientLightShader.fs";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();

	this->UpdateAmbientLight();
	this->UpdateFogDensity();
	this->UpdateFogGradient();
	this->UpdateSkyColor();
}

HMEngine::Core::Rendering::Shaders::AmbientLightShader::~AmbientLightShader()
{
}