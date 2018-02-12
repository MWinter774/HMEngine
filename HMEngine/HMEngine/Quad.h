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
		class OpenGLQuad;
		class UITexture;
	}

	namespace UI
	{
		class Quad
		{
			friend class HMEngine::GameEngine;
			typedef struct QuadDetails
			{
				glm::vec2 position;
				glm::vec2 scale;
				glm::vec2 topLeft;
				glm::vec2 bottomRight;
				float width;
				float height;
			} QuadDetails;
		public:
			Quad(const std::string& name, const std::string& texturePath, const std::vector<glm::vec2>& vertices, const glm::vec2& position, const glm::vec2& scale);
			Quad(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale);
			virtual ~Quad();
			Quad(const HMEngine::UI::Quad& other);
			HMEngine::UI::Quad& operator=(const HMEngine::UI::Quad& other);

			virtual HMEngine::UI::Quad* Clone() const = 0;

			virtual inline void Update() {}
			virtual inline void AttachToGameEngineEvent() {}

			void AddTexture(const std::string& texturePath);

			inline std::string GetName() const { return this->_name; }
			inline glm::vec2 GetPosition() const { return this->_quadDetails.position; }
			inline glm::vec2 GetScale() const { return this->_quadDetails.scale; }
			inline float GetWidth() const { return this->_quadDetails.width; }
			inline float GetHeight() const { return this->_quadDetails.height; }
			inline HMEngine::Core::Transform& GetTransform() { return *this->_transform; }

			inline void SetPosition(const glm::vec2& position) { this->_quadDetails.position = position; this->UpdateQuadDetails(); this->UpdateTransform(); }
			inline void SetScale(const glm::vec2& scale) { this->_quadDetails.scale = scale; this->UpdateQuadDetails(); this->UpdateTransform(); }
			void SetTexture(unsigned int i = 0);

			void BindTexture() const;
			void Draw() const;

		protected:
			static const std::vector<glm::vec2> rectangle;

			std::string _name;
			HMEngine::OpenGL::OpenGLQuad* _quad;
			HMEngine::UI::Quad::QuadDetails _quadDetails;

			bool _isAddedToGameEngine;

			HMEngine::GameEngine* _gameEngine;

		private:
			HMEngine::OpenGL::UITexture* _currentTexture;
			std::vector<HMEngine::OpenGL::UITexture*> _textures;
			HMEngine::Core::Transform* _transform;
			std::vector<glm::vec2> _vertices;

			virtual void AttachToGameEngine();

			void UpdateTransform();
			void UpdateQuadDetails();
		};
	}
}