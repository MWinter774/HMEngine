#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <glm\glm.hpp>
#include <unordered_map>
#include <GL\glew.h>
#include "Utilities.h"
#include "DirectionalLight.h"

namespace HMEngine
{
	namespace Components
	{
		class Texture;
	}

	namespace Core
	{
		class GameObject;
		class Transform;

		namespace Rendering
		{
			class Camera;
			namespace Shaders
			{
				template<typename T>
				class Shader
				{
					friend class HMEngine::Core::GameObject;
				public:
					static T& GetInstance()
					{
						static T& instance = T();
						return instance;
					};

					void AddVertexShader(const std::string& shaderFilePath);
					void AddFragmentShader(const std::string& shaderFilePath);
					void AddGeometryShader(const std::string& shaderFilePath);
					void Compile() const;
					void Bind() const;

					void SetUniform(const std::string& uniformName, int value);
					void SetUniform(const std::string& uniformName, float value);
					void SetUniform(const std::string& uniformName, const glm::vec3& value);
					void SetUniform(const std::string& uniformName, const glm::mat4& value);

					virtual void UpdateUniforms(const HMEngine::Core::Transform& transform) { }
					virtual void UpdateUniforms(const HMEngine::Components::DirectionalLight& directionalLight) { }

				protected:
					static std::string ReadFileContent(const std::string& filePath);
					static void CheckForErrors(GLuint programId, GLenum flag, bool isProgram);

					Shader() : _program(-1)
					{
						this->_program = glCreateProgram();
						if (!this->_program) //if program is 0 that means an error occured
						{
							HMEngine::Core::Utilities::ThrowException("SHADER PROGRAM CREATION FAILED!!!", "Shader Error");
						}
					}
					virtual ~Shader()
					{
						glDeleteProgram(this->_program);
					}
					Shader(const Shader& other) = delete;
					Shader& operator=(const Shader& other) = delete;

					void AddShader(const std::string& code, GLenum type);
					void AddUniform(const std::string& uniformName);

				private:
					GLuint _program;
					std::unordered_map<std::string, int> _uniforms; //maps between a uniform name and a id of that uniform
				};

				/*
				Reads the content of a file and returns the content.
				Input:
				shaderFilePath - path to the file
				Output:
				The content of the file.
				*/
				template<typename T>
				std::string Shader<T>::ReadFileContent(const std::string& filePath)
				{
					std::string file;
					std::string line;
					std::ifstream shaderFile = std::ifstream();
					shaderFile.open(filePath.c_str());
					if (!shaderFile.is_open())
					{
						HMEngine::Core::Utilities::ThrowException("COULDN'T OPEN " + filePath + "!!!!", "Shader Error");
					}

					while (std::getline(shaderFile, line))
					{
						file += line;
						if (!shaderFile.eof()) file += '\n';
					}

					shaderFile.close();
					return file;
				}

				/*
				Check for compilation errors from the shaders/program.
				Input:
				programId - the id of the program/shader to check for error
				flag - the kind of errors to check
				isProgram - is it a program or a shader
				*/
				template<typename T>
				inline void Shader<T>::CheckForErrors(GLuint programId, GLenum flag, bool isProgram)
				{
					GLint success = 0;
					GLchar infoLog[1024] = { 0 };

					if (isProgram)
						glGetProgramiv(programId, flag, &success);
					else
						glGetShaderiv(programId, flag, &success);

					if (!success)
					{
						if (isProgram)
							glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
						else
							glGetShaderInfoLog(programId, sizeof(infoLog), NULL, infoLog);

						HMEngine::Core::Utilities::ThrowException(infoLog, "GLSL Error");
					}
				}

				/*
				Adds a shader code to the shader program.
				Input:
				code - the code of the shader
				type - the shader type
				*/
				template<typename T>
				inline void Shader<T>::AddShader(const std::string& code, GLenum type)
				{
					GLuint shader = glCreateShader(type);
					if (!shader) HMEngine::Core::Utilities::ThrowException("SHADER CREATION FAILED!!!", "Shader Error");

					const GLchar* p[1];
					p[0] = code.c_str();
					GLint lengths[1];
					lengths[0] = code.length();
					glShaderSource(shader, 1, p, lengths);
					glCompileShader(shader);
					this->CheckForErrors(shader, GL_COMPILE_STATUS, false);
					glAttachShader(this->_program, shader);
				}

				/*
				Adds uniform to the uniform map.
				Input:
				uniformName - name of the uniform in the code
				*/
				template<typename T>
				inline void Shader<T>::AddUniform(const std::string& uniformName)
				{
					GLuint uniformId = glGetUniformLocation(this->_program, uniformName.c_str());
					if (uniformId == 0xFFFFFFFF)
						HMEngine::Core::Utilities::ThrowException("ERROR GETTING UNIFORM \"" + uniformName + "\"", "Shader Error");

					this->_uniforms[uniformName] = uniformId;
				}

				/*
				Adds the vertex shader to the shader program.
				Input:
				shaderFilePath - path to the shader file
				*/
				template<typename T>
				inline void Shader<T>::AddVertexShader(const std::string& shaderFilePath)
				{
					this->AddShader(this->ReadFileContent(shaderFilePath), GL_VERTEX_SHADER);
				}

				/*
				Adds the fragment shader to the shader program.
				Input:
				shaderFilePath - path to the shader file
				*/
				template<typename T>
				inline void Shader<T>::AddFragmentShader(const std::string& shaderFilePath)
				{
					this->AddShader(this->ReadFileContent(shaderFilePath), GL_FRAGMENT_SHADER);
				}

				/*
				Adds the geometry shader to the shader program.
				Input:
				shaderFilePath - path to the shader file
				*/
				template<typename T>
				inline void Shader<T>::AddGeometryShader(const std::string& shaderFilePath)
				{
					this->AddShader(this->ReadFileContent(shaderFilePath), GL_GEOMETRY_SHADER);
				}

				/*
				Compiles shader.
				*/
				template<typename T>
				inline void Shader<T>::Compile() const
				{
					glLinkProgram(this->_program);
					this->CheckForErrors(this->_program, GL_LINK_STATUS, true);

					glValidateProgram(this->_program);
					this->CheckForErrors(this->_program, GL_VALIDATE_STATUS, true);
				}

				/*
				Binds shader.
				*/
				template<typename T>
				inline void Shader<T>::Bind() const
				{
					glUseProgram(this->_program);
				}

				template<typename T>
				inline void Shader<T>::SetUniform(const std::string& uniformName, int value)
				{
					if (this->_uniforms.find(uniformName) == this->_uniforms.end())
						this->AddUniform(uniformName);
					glUniform1i(this->_uniforms[uniformName], value);
				}

				template<typename T>
				inline void Shader<T>::SetUniform(const std::string& uniformName, float value)
				{
					if (this->_uniforms.find(uniformName) == this->_uniforms.end())
						this->AddUniform(uniformName);
					glUniform1f(this->_uniforms[uniformName], value);
				}

				template<typename T>
				inline void Shader<T>::SetUniform(const std::string& uniformName, const glm::vec3& value)
				{
					if (this->_uniforms.find(uniformName) == this->_uniforms.end())
						this->AddUniform(uniformName);
					glUniform3f(this->_uniforms[uniformName], value.x, value.y, value.z);
				}

				template<typename T>
				inline void Shader<T>::SetUniform(const std::string& uniformName, const glm::mat4& value)
				{

					if (this->_uniforms.find(uniformName) == this->_uniforms.end())
						this->AddUniform(uniformName);
					glUniformMatrix4fv(this->_uniforms[uniformName], 1, GL_FALSE, glm::value_ptr(value));
				}
			}
		}
	}
}