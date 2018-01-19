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

HMEngine::Core::Rendering::Shaders::AmbientLightShader::AmbientLightShader()
{
	std::string vs = "./resources/shaders/ambientLightShader.vs";
	std::string fs = "./resources/shaders/ambientLightShader.fs";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();

	this->UpdateAmbientLight();
}

HMEngine::Core::Rendering::Shaders::AmbientLightShader::~AmbientLightShader()
{
}