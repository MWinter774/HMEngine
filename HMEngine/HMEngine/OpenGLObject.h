#pragma once
#include "GL\glew.h"
#include "glm\glm.hpp"
#include <vector>
#include <any>
#include <iostream>

namespace HMEngine
{
	namespace OpenGL
	{
		class OpenGLObject
		{
			typedef std::vector<glm::vec2> UVBuffer;
			typedef std::vector<glm::vec3> VerticesBuffer;
			typedef std::vector<GLuint> IndicesBuffer;
		public:
			template <class T, class ... Args>
			OpenGLObject(T& first, Args&... args);
			virtual ~OpenGLObject();
			OpenGLObject(const HMEngine::OpenGL::OpenGLObject& other);
			HMEngine::OpenGL::OpenGLObject& operator=(const HMEngine::OpenGL::OpenGLObject& other);

			inline std::vector<std::any> GetVBOData() const { return this->_vboData; }

		private:
			static void ConvertAnyToType(std::any);

			GLuint _vao;
			std::vector<GLuint> _vbo;
			std::vector<std::any> _vboData;
			unsigned int _vboCount;
			unsigned int _vboCounter;

			void InitVBOFromVector();
			template <class T, class ... Args>
			void InitVBO(T& first, Args&... args);
			inline void InitVBO() {}

			void InitBuffers();

			void DeleteBuffers();
		};

		template<class T, class ...Args>
		inline OpenGLObject::OpenGLObject(T& first, Args&... args) : _vboCount(sizeof...(args)+1), _vboCounter(0), _vboData()
		{
			if (typeid(std::vector<std::any>&) == typeid(first) && sizeof...(args) == 0)
			{
				this->_vboData = first;
				this->_vboCount = this->_vboData.size();
				this->_vboCounter = 0;
				this->InitBuffers();
				this->InitVBOFromVector();
			}
			else
			{
				this->InitBuffers();
				this->InitVBO(first, args...);
			}
		}

		template<class T, class ...Args>
		inline void OpenGLObject::InitVBO(T& first, Args&...args)
		{
			int sizeOfElement = typeid(first[0]) == typeid(GLuint) ? 1 : typeid(first[0]) == typeid(glm::vec2) ? 2 : typeid(first[0]) == typeid(glm::vec3) ? 3 : 4;
			glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[this->_vboCounter]);
			glBufferData(GL_ARRAY_BUFFER, first.size() * sizeof(first[0]), &first[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(this->_vboCounter);
			glVertexAttribPointer(this->_vboCounter, sizeOfElement, GL_FLOAT, GL_FALSE, 0, (void*)0);
			this->_vboData.push_back(first);
			this->_vboCounter++;
			this->InitVBO(args...);
		}
	}
}