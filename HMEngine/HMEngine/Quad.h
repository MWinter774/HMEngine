#pragma once
#include <string>
#include <vector>
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "Transform.h"

namespace HMEngine
{
	class GameEngine;
	namespace OpenGL
	{
		class UITexture;
	}

	namespace UI
	{
		class Quad
		{
			friend class HMEngine::GameEngine;
		public:
			Quad(const std::string& name, const std::string& texturePath, const std::vector<glm::vec2>& vertices, const glm::vec2& position, const glm::vec2& scale);
			virtual ~Quad();
			Quad(const HMEngine::UI::Quad& other);
			HMEngine::UI::Quad& operator=(const HMEngine::UI::Quad& other);

			virtual HMEngine::UI::Quad* Clone() const = 0;

			virtual inline void Update() {}
			virtual inline void AttachToGameEngineEvent() {}

			inline std::string GetName() const { return this->_name; }
			inline glm::vec2 GetPosition() const { return this->_position; }
			inline glm::vec2 GetScale() const { return this->_scale; }
			inline HMEngine::Core::Transform& GetTransform() { return *this->_transform; }

			void SetPosition(const glm::vec2& position) { this->_position = position; this->_transform->SetPosition(glm::vec3(position, 0.0f)); }
			void SetScale(const glm::vec2& scale) { this->_scale = scale; this->_transform->SetScale(glm::vec3(scale, 1.0f)); }

			void BindTexture() const;
			void Draw() const;

		protected:
			static const std::vector<glm::vec2> rectangle;

			HMEngine::OpenGL::UITexture* _texture;
			std::string _name;
			std::vector<glm::vec2> _vertices;
			glm::vec2 _position;
			glm::vec2 _scale;
			HMEngine::Core::Transform* _transform;
			bool _isAddedToGameEngine;

			virtual void AttachToGameEngine();

			HMEngine::GameEngine* _gameEngine;

		private:
			enum
			{
				VBO_VERTICES,

				VBO_COUNT
			};
			GLuint _vao;
			GLuint _vbo[VBO_COUNT];

			void InitBuffers();
		};
	}
}