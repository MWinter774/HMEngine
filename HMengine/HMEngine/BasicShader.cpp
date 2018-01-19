#include "BasicShader.h"
#include "Transform.h"
#include "GameSettings.h"

HMEngine::Core::Rendering::Shaders::BasicShader::BasicShader()
{
	std::string vs = "./resources/shaders/basicShader.vs";
	std::string fs = "./resources/shaders/basicShader.fs";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();

	this->UpdateAmbientLight();
	this->UpdateFogDensity();
	this->UpdateFogGradient();
	this->UpdateSkyColor();
}

HMEngine::Core::Rendering::Shaders::BasicShader::~BasicShader()
{
}

void HMEngine::Core::Rendering::Shaders::BasicShader::UpdateUniforms(const HMEngine::Core::Transform& transform)
{
	this->SetUniform("transformationMatrix", transform.GetModelMatrix());
	this->SetUniform("viewMatrix", transform.GetViewMatrix());
	this->SetUniform("projectionMatrix", HMEngine::GameSettings::GetProjectionMatrix());
}

void HMEngine::Core::Rendering::Shaders::BasicShader::UpdateAmbientLight()
{
	this->SetUniform("ambientLight", HMEngine::GameSettings::GetAmbientLight());
}

void HMEngine::Core::Rendering::Shaders::BasicShader::UpdateFogDensity()
{
	this->SetUniform("fogDensity", HMEngine::GameSettings::GetFogDensity());
}

void HMEngine::Core::Rendering::Shaders::BasicShader::UpdateFogGradient()
{
	this->SetUniform("fogGradient", HMEngine::GameSettings::GetFogGradient());
}

void HMEngine::Core::Rendering::Shaders::BasicShader::UpdateSkyColor()
{
	this->SetUniform("skyColor", HMEngine::GameSettings::GetSkyColor());
}