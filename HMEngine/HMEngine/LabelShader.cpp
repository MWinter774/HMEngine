#include "LabelShader.h"
#include "Transform.h"

void HMEngine::Core::Rendering::Shaders::LabelShader::UpdateUniforms(const HMEngine::Core::Transform& transform)
{
	this->SetUniform("transformationMatrix", transform.GetModelMatrix());
}

HMEngine::Core::Rendering::Shaders::LabelShader::LabelShader()
{
	std::string vs = "./resources/shaders/labelShader.vs";
	std::string fs = "./resources/shaders/labelShader.fs";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();
}

HMEngine::Core::Rendering::Shaders::LabelShader::~LabelShader()
{
}