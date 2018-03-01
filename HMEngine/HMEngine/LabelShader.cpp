#include "LabelShader.h"
#include "Transform.h"
#include "Label.h"
#include "GameSettings.h"

void HMEngine::Core::Rendering::Shaders::LabelShader::UpdateUniforms(HMEngine::UI::Label& label)
{
	auto labelPos = label.GetPosition();
	auto goodPos = glm::vec2(labelPos.x / float(HMEngine::GameSettings::GetWindowWidth()), labelPos.y / HMEngine::GameSettings::GetWindowHeight());
	this->SetUniform("translation", goodPos);
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