#pragma once
#include <string>
#include <vector>
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "Transform.h"
#include "GameSettings.h"

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

			void SetPosition(const glm::vec2& position);
			void SetScale(const glm::vec2& scale);

			void BindTexture() const;
			void Draw() const;

		protected:
			static const std::vector<glm::vec2> rectangle;

			std::string _name;
			glm::vec2 _position;
			glm::vec2 _scale;
			glm::vec2 _topLeft;
			glm::vec2 _bottomRight;
			float _width;
			float _height;

			bool _isAddedToGameEngine;

			HMEngine::GameEngine* _gameEngine;

		private:
			enum
			{
				VBO_VERTICES,

				VBO_COUNT
			};
			HMEngine::OpenGL::UITexture* _texture;
			std::vector<glm::vec2> _vertices;
			HMEngine::Core::Transform* _transform;
			GLuint _vao;
			GLuint _vbo[VBO_COUNT];
			virtual void AttachToGameEngine();

			inline void UpdateQuadDetails()
			{
				this->_width = this->_scale.x * HMEngine::GameSettings::GetWindowWidth();
				this->_height = this->_scale.y * HMEngine::GameSettings::GetWindowHeight();
				this->_topLeft = glm::vec2(this->_position.x - this->_width / 2, this->_position.y - this->_height / 2);
				this->_bottomRight = glm::vec2(this->_position.x + this->_width / 2, this->_position.y + this->_height / 2);
			}
			void InitBuffers();
		};
	}
}