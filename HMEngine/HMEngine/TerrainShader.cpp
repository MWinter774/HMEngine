#include "TerrainShader.h"
#include "GameSettings.h"
#include "Transform.h"

void HMEngine::Core::Rendering::Shaders::TerrainShader::UpdateUniforms(const HMEngine::Core::Transform& transform)
{
	this->SetUniform("transformationMatrix", transform.GetModelMatrix());
	this->SetUniform("viewMatrix", transform.GetViewMatrix());
	this->SetUniform("projectionMatrix", HMEngine::GameSettings::GetProjectionMatrix());
}

void HMEngine::Core::Rendering::Shaders::TerrainShader::UpdateAmbientLight()
{
	this->SetUniform("ambientLight", HMEngine::GameSettings::GetAmbientLight());
}

void HMEngine::Core::Rendering::Shaders::TerrainShader::UpdateFogDensity()
{
	this->SetUniform("fogDensity", HMEngine::GameSettings::GetFogDensity());
}

void HMEngine::Core::Rendering::Shaders::TerrainShader::UpdateFogGradient()
{
	this->SetUniform("fogGradient", HMEngine::GameSettings::GetFogGradient());
}

void HMEngine::Core::Rendering::Shaders::TerrainShader::UpdateSkyColor()
{
	this->SetUniform("skyColor", HMEngine::GameSettings::GetSkyColor());
}

HMEngine::Core::Rendering::Shaders::TerrainShader::TerrainShader()
{
	std::string vs = "./resources/shaders/terrainShader.vs";
	std::string fs = "./resources/shaders/terrainShader.fs";

	this->AddVertexShader(vs);
	this->AddFragmentShader(fs);

	this->Compile();
	this->Bind();

	this->UpdateAmbientLight();
	this->UpdateFogDensity();
	this->UpdateFogGradient();
	this->UpdateSkyColor();
}

HMEngine::Core::Rendering::Shaders::TerrainShader::~TerrainShader()
{
}