#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "Transform.h"
#include <map>
#include "OpenGLQuad.h"
#include "EventObject.h"

namespace HMEngine
{
	class GameEngine;
	namespace OpenGL
	{
		class UITexture;
	}

	namespace UI
	{
		class Quad : public HMEngine::Core::EventObject
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
			Quad(const std::string& name, const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale, bool useVertices = true);
			Quad(const std::string& name, const glm::vec2& position, const glm::vec2& scale);

			virtual ~Quad();
			Quad(const HMEngine::UI::Quad& other);
			HMEngine::UI::Quad& operator=(const HMEngine::UI::Quad& other);

			virtual HMEngine::UI::Quad* Clone() const = 0;

			void AddTexture(const std::string& texturePath);

			inline std::string GetName() const { return this->_name; }
			inline glm::vec2 GetPosition() const { return this->_quadDetails.position; }
			inline glm::vec2 GetScale() const { return this->_quadDetails.scale; }
			inline float GetWidth() const { return this->_quadDetails.width; }
			inline float GetHeight() const { return this->_quadDetails.height; }
			inline HMEngine::Core::Transform& GetTransform() { return *this->_transform; }

			inline void SetPosition(const glm::vec2& position) { this->_quadDetails.position = position; this->UpdateQuadDetails(); this->UpdateTransform(); }
			inline void SetPosition(float x, float y) { this->_quadDetails.position.x = x; this->_quadDetails.position.y = y; this->UpdateQuadDetails(); this->UpdateTransform(); }
			inline void SetScale(const glm::vec2& scale) { this->_quadDetails.scale = scale; this->UpdateQuadDetails(); this->UpdateTransform(); }
			inline void SetScale(float scaleX, float scaleY) { this->_quadDetails.scale.x = scaleX; this->_quadDetails.scale.y = scaleY; this->UpdateQuadDetails(); this->UpdateTransform(); }
			void SetTexture(unsigned int i = 0);

			void BindTexture() const;
			virtual void Draw() const;

		protected:
			static const std::vector<glm::vec2> rectangle;

			inline void SetVertices(const std::vector<glm::vec2>& vertices) { this->_openglQuad->SetVertices(vertices); }
			inline void SetUVs(const std::vector<glm::vec2>& uvs) { this->_openglQuad->SetUVs(uvs); }

			std::string _name;
			HMEngine::UI::Quad::QuadDetails _quadDetails;
			HMEngine::OpenGL::OpenGLQuad* _openglQuad;
			HMEngine::GameEngine* _gameEngine;

		private:
			bool _isAttachedToGameEngine;
			HMEngine::OpenGL::UITexture* _currentTexture;
			std::vector<HMEngine::OpenGL::UITexture*> _quadTextures;
			HMEngine::Core::Transform* _transform;

			virtual void AttachToGameEngine(HMEngine::GameEngine& gameEngine);

			void UpdateTransform();
			void UpdateQuadDetails();
		};
	}
}