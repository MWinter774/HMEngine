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
#include <functional>

namespace HMEngine
{
	class GameEngine;
	namespace OpenGL
	{
		class UITexture;
	}
	namespace Core
	{
		namespace Rendering
		{
			class RenderingEngine;
		}
	}

	namespace UI
	{
		class Label;

		class Quad : public HMEngine::Core::EventObject
		{
			friend class HMEngine::GameEngine;
			friend class HMEngine::Core::Rendering::RenderingEngine;
			typedef struct QuadDetails
			{
				glm::vec2 position;
				glm::vec2 scale;
				glm::vec2 topLeft;
				glm::vec2 bottomRight;
				float width;
				float height;
			} QuadDetails;
			typedef struct
			{
				HMEngine::UI::Label* label;
				HMEngine::UI::Quad* quad;
			} QuadType;
		public:
			std::function<void()> _hideEvent;

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
			inline glm::vec2 GetTopLeft() const { return this->_quadDetails.topLeft; }
			inline glm::vec2 GetBottomRight() const { return this->_quadDetails.bottomRight; }
			inline HMEngine::Core::Transform& GetTransform() { return *this->_transform; }
			inline bool IsVisible() const { return this->_isVisible; }
			inline std::vector<HMEngine::UI::Quad*> GetChilds() const { return this->_childs; }

			inline void SetPosition(const glm::vec2& position) { this->_quadDetails.position = position; this->UpdateQuadDetails(); }
			inline void SetPosition(float x, float y) { this->_quadDetails.position.x = x; this->_quadDetails.position.y = y; this->UpdateQuadDetails(); }
			inline void SetScale(const glm::vec2& scale) { this->_quadDetails.scale = scale; this->UpdateQuadDetails(); }
			inline void SetScale(float scaleX, float scaleY) { this->_quadDetails.scale.x = scaleX; this->_quadDetails.scale.y = scaleY; this->UpdateQuadDetails(); }
			void SetTexture(unsigned int i = 0);
			void SetTopLeft(const glm::vec2& topLeft);
			void SetCenter(const glm::vec2& center);
			virtual inline void Show();
			virtual inline void ShowEvent() {}
			virtual inline void Hide();
			virtual inline void HideEvent() {}
			virtual inline void SetVisiblity(bool isVisible);
			void AddChild(HMEngine::UI::Quad* other);
			void AddChild(const HMEngine::UI::Quad& other);

			void BringToFront();

			void BindTexture() const;
			virtual void Draw() const;

			void DisableEvents();
			void EnableEvents();

		protected:
			static const std::vector<glm::vec2> rectangle;

			inline void SetVertices(const std::vector<glm::vec2>& vertices) { this->_openglQuad->SetVertices(vertices); }
			inline void SetUVs(const std::vector<glm::vec2>& uvs) { this->_openglQuad->SetUVs(uvs); }
			void AddChild(unsigned int index, HMEngine::UI::Quad* other);

			std::string _name;
			HMEngine::UI::Quad::QuadDetails _quadDetails;
			HMEngine::OpenGL::OpenGLQuad* _openglQuad;
			HMEngine::GameEngine* _gameEngine;
			bool _isVisible;
			HMEngine::OpenGL::UITexture* _currentTexture;

		private:
			bool _isAttachedToGameEngine;
			std::vector<HMEngine::OpenGL::UITexture*> _quadTextures;
			HMEngine::Core::Transform* _transform;
			std::vector<HMEngine::UI::Quad::QuadType> _childsRenderingEngineFormat;
			std::vector<HMEngine::UI::Quad*> _childs;

			virtual void AttachToGameEngine(HMEngine::GameEngine& gameEngine);

			void UpdateTransform();
			void UpdateQuadDetails();
		};
	}
}