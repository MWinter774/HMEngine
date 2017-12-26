#include "Shader.h"

HMEngine::Core::Rendering::Shaders::BasicShader::BasicShader()
{
	std::string vs = "..\\Debug\\basicShaderVs.txt";
	std::string fs = "..\\Debug\\basicShaderFs.txt";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();

}

void HMEngine::Core::Rendering::Shaders::BasicShader::UpdateUniforms(const HMEngine::Core::Transform& transform)
{
	this->SetUniform("transformationMatrix", transform.GetModelMatrix());
	this->SetUniform("viewMatrix", transform.GetViewMatrix());
	this->SetUniform("projectionMatrix", HMEngine::GameSettings::GetProjectionMatrix());
};