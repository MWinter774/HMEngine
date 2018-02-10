#include "UIShader.h"
#include <string>
#include "Transform.h"

void HMEngine::Core::Rendering::Shaders::UIShader::UpdateUniforms(const HMEngine::Core::Transform& transform)
{
	this->SetUniform("transformationMatrix", transform.GetModelMatrix());
}

HMEngine::Core::Rendering::Shaders::UIShader::UIShader()
{
	std::string vs = "./resources/shaders/uiShader.vs";
	std::string fs = "./resources/shaders/uiShader.fs";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();
}

HMEngine::Core::Rendering::Shaders::UIShader::~UIShader()
{
}