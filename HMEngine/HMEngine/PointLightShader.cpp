#include "PointLightShader.h"
#include "Transform.h"
#include "GameSettings.h"
#include "PointLight.h"

void HMEngine::Core::Rendering::Shaders::PointLightShader::UpdateUniforms(const HMEngine::Core::Transform& transform)
{
	this->SetUniform("transformationMatrix", transform.GetModelMatrix());
	this->SetUniform("viewMatrix", transform.GetViewMatrix());
	this->SetUniform("projectionMatrix", HMEngine::GameSettings::GetProjectionMatrix());
	//this->SetUniform("ambientLight", HMEngine::GameSettings::GetAmbientLight());
}

void HMEngine::Core::Rendering::Shaders::PointLightShader::UpdateUniforms(const HMEngine::Components::PointLight& pointLight)
{
	/*this->SetUniform("pointLight.base.color", pointLight.GetBase().GetColor());
	this->SetUniform("pointLight.base.intensity", pointLight.GetBase().GetIntensity());
	this->SetUniform("pointLight.attenuation", pointLight.GetAttenuation());
	this->SetUniform("pointLight.position", pointLight.GetPosition());
	this->SetUniform("pointLight.range", pointLight.GetRange());*/
	this->SetUniform("pointLight.base.color", glm::vec3(0,1,0));
	this->SetUniform("pointLight.base.intensity", 5.0f);
	this->SetUniform("pointLight.attenuation", glm::vec3(1,0,0));
	this->SetUniform("pointLight.position", glm::vec3(0,1,0));
	this->SetUniform("pointLight.range", 10.0f);
}

HMEngine::Core::Rendering::Shaders::PointLightShader::PointLightShader()
{
	std::string vs = "./resources/shaders/pointLightShader.vs";
	std::string fs = "./resources/shaders/pointLightShader.fs";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();
}

HMEngine::Core::Rendering::Shaders::PointLightShader::~PointLightShader()
{
}