#include "LabelShader.h"
#include "Transform.h"
#include "Label.h"

void HMEngine::Core::Rendering::Shaders::LabelShader::UpdateUniforms(HMEngine::UI::Label& label)
{
	this->SetUniform("transformationMatrix", label.GetTransform().GetModelMatrix());
	this->SetUniform("textColor", label.GetColor());
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