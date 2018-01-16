#include "DirectionalLightShader.h"
#include "Transform.h"
#include "GameSettings.h"

void HMEngine::Core::Rendering::Shaders::DirectionalLightShader::UpdateUniforms(const HMEngine::Core::Transform& transform)
{
	this->SetUniform("transformationMatrix", transform.GetModelMatrix());
	this->SetUniform("viewMatrix", transform.GetViewMatrix());
	this->SetUniform("projectionMatrix", HMEngine::GameSettings::GetProjectionMatrix());
	this->SetUniform("ambientLight", HMEngine::GameSettings::GetAmbientLight());
}

void HMEngine::Core::Rendering::Shaders::DirectionalLightShader::UpdateUniforms(const HMEngine::Components::DirectionalLight& directionalLight)
{
	this->SetUniform("directionalLight.base.color", directionalLight.GetBase().GetColor());
	this->SetUniform("directionalLight.base.intensity", directionalLight.GetBase().GetIntensity());
	this->SetUniform("directionalLight.direction", directionalLight.GetDirection());
}

HMEngine::Core::Rendering::Shaders::DirectionalLightShader::DirectionalLightShader()
{
	std::string vs = "./resources/shaders/directionalLightShader.vs";
	std::string fs = "./resources/shaders/directionalLightShader.fs";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();
}

HMEngine::Core::Rendering::Shaders::DirectionalLightShader::~DirectionalLightShader()
{
}