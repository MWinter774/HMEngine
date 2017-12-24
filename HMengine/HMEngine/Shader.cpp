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

void HMEngine::Core::Rendering::Shaders::BasicShader::Update(HMEngine::Core::Transform tr)
{
	glUniformMatrix4fv(this->_uniforms["MVP"], 1, GL_FALSE, glm::value_ptr(tr.GetMVPMatrix()));
}
