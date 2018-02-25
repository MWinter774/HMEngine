#include "LabelShader.h"
#include "Transform.h"
#include "Label.h"
#include "GameSettings.h"

void HMEngine::Core::Rendering::Shaders::LabelShader::UpdateUniforms(HMEngine::UI::Label& label)
{
	auto goodPos = glm::vec2(label.GetPosition());
	auto ggPos = glm::vec2((goodPos.x - (label.GetWidth() / 2.0f)) / HMEngine::GameSettings::GetWindowWidth(), 
		(goodPos.y - (label.GetHeight() / 2.0f)) / HMEngine::GameSettings::GetWindowHeight());
	ggPos = goodPos;
	ggPos /= glm::vec2(HMEngine::GameSettings::GetWindowWidth(), HMEngine::GameSettings::GetWindowHeight());
	this->SetUniform("translation", ggPos);
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