#include "DirectionalLight.h"
#include "BasicShader.h"
#include "GameObject.h"
#include "BaseLight.h"

HMEngine::Components::DirectionalLight::DirectionalLight(HMEngine::Components::BaseLight& base, glm::vec3 direction)
{
	this->_direction = glm::normalize(direction);
	this->_base = &base;
}

void HMEngine::Components::DirectionalLight::UpdateEvent()
{
	HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().UpdateUniforms(*this);
}

HMEngine::Components::DirectionalLight& HMEngine::Components::DirectionalLight::operator=(HMEngine::Components::DirectionalLight& other)
{
	if (this != &other)
	{
		this->SetBase(*other.GetBase());
		this->SetDirection(other.GetDirection());
	}
	return *this;
}



//void HMEngine::Components::DirectionalLight::RenderEvent()
//{
//	HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().Bind();
//	HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().UpdateUniforms(this->_parentObject->GetTransform());
//
//	this->_texture->Bind();
//
//	glBindVertexArray(this->_vao);
//
//	glDrawArrays(GL_TRIANGLES, 0, this->_mesh->GetVertices().size());
//
//}
