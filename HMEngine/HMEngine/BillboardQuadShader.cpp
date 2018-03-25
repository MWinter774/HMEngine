#include "BillboardQuadShader.h"
#include "Transform.h"
#include "Camera.h"
#include "GameSettings.h"

void HMEngine::Core::Rendering::Shaders::BillboardQuadShader::UpdateUniforms(const HMEngine::Core::Transform& transform)
{
	glm::mat4 viewMatrix = this->_camera->GetViewMatrix();
	this->SetUniform("CameraRight_worldspace", glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]));
	this->SetUniform("CameraUp_worldspace", glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]));
	this->SetUniform("VP", this->_projectionMatrix * viewMatrix);
	this->SetUniform("BillboardPos", transform.GetPosition());
	this->SetUniform("BillboardSize", glm::vec2(transform.GetScale()));
}

HMEngine::Core::Rendering::Shaders::BillboardQuadShader::BillboardQuadShader() : _camera(&HMEngine::Core::Rendering::Camera::GetInstance()),
_projectionMatrix(HMEngine::GameSettings::GetProjectionMatrix())
{
	std::string vs = "./resources/shaders/billboardQuadShader.vs";
	std::string fs = "./resources/shaders/billboardQuadShader.fs";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();
}

HMEngine::Core::Rendering::Shaders::BillboardQuadShader::~BillboardQuadShader()
{
}