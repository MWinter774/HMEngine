#include "BasicShader.h"

HMEngine::Core::Rendering::Shaders::BasicShader::BasicShader()
{
	std::string vs = "./shaders/basicShader.vs";
	std::string fs = "./shaders/basicShader.fs";

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
}
