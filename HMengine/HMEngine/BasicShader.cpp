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
}

HMEngine::Core::Rendering::Shaders::BasicShader::~BasicShader()
{
}

void HMEngine::Core::Rendering::Shaders::BasicShader::UpdateUniforms(const HMEngine::Core::Transform& transform)
{
	this->SetUniform("transformationMatrix", transform.GetModelMatrix());
	this->SetUniform("viewMatrix", transform.GetViewMatrix());
	this->SetUniform("projectionMatrix", HMEngine::GameSettings::GetProjectionMatrix());
	this->SetUniform("transform", transform.GetModelMatrix() * HMEngine::GameSettings::GetProjectionMatrix());
	this->SetUniform("ambientLight", HMEngine::GameSettings::GetAmbientLight());
}

void HMEngine::Core::Rendering::Shaders::BasicShader::UpdateUniforms(HMEngine::Components::DirectionalLight& directionalLight)
{
	this->SetUniform("directionalLight.base.color", directionalLight.GetBase()->GetColor());
	this->SetUniform("directionalLight.base.intensity", directionalLight.GetBase()->GetIntensity());
	this->SetUniform("directionalLight.direction", directionalLight.GetDirection());
}