#pragma once
#include "Component.h"
#include <vector>
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Components
	{
		class DebugComponent : public HMEngine::Components::Component
		{
		public:
			DebugComponent();
			~DebugComponent();

			HMEngine::Components::Component* Clone() override;

			void UpdateEvent() override;
		private:
			std::vector<glm::vec3> vertices =
			{
				glm::vec3(1,  1,  1),
				glm::vec3(-1,  1,  1),
				glm::vec3(-1, -1,  1),
				glm::vec3(1, -1,  1),
				glm::vec3(1, -1, -1),
				glm::vec3(-1, -1, -1),
				glm::vec3(-1,  1, -1),
				glm::vec3(1,  1, -1),
			};
			std::vector<GLuint> indices =
			{
				0, 1, 2, 2, 3, 0,           // Front face
				7, 4, 5, 5, 6, 7,           // Back face
				6, 5, 2, 2, 1, 6,           // Left face
				7, 0, 3, 3, 4, 7,           // Right face
				7, 6, 1, 1, 0, 7,           // Top face
				3, 2, 5, 5, 4, 3            // Bottom face
			};

			std::vector<glm::vec2> uvs = {
				glm::vec2(0.000059f, 1.0f - 0.000004f),
				glm::vec2(0.000103f, 1.0f - 0.336048f),
				glm::vec2(0.335973f, 1.0f - 0.335903f),
				glm::vec2(1.000023f, 1.0f - 0.000013f),
				glm::vec2(0.667979f, 1.0f - 0.335851f),
				glm::vec2(0.999958f, 1.0f - 0.336064f),
				glm::vec2(0.667979f, 1.0f - 0.335851f),
				glm::vec2(0.336024f, 1.0f - 0.671877f),
				glm::vec2(0.667969f, 1.0f - 0.671889f),
				glm::vec2(1.000023f, 1.0f - 0.000013f),
				glm::vec2(0.668104f, 1.0f - 0.000013f),
				glm::vec2(0.667979f, 1.0f - 0.335851f),
				glm::vec2(0.000059f, 1.0f - 0.000004f),
				glm::vec2(0.335973f, 1.0f - 0.335903f),
				glm::vec2(0.336098f, 1.0f - 0.000071f),
				glm::vec2(0.667979f, 1.0f - 0.335851f),
				glm::vec2(0.335973f, 1.0f - 0.335903f),
				glm::vec2(0.336024f, 1.0f - 0.671877f),
				glm::vec2(1.000004f, 1.0f - 0.671847f),
				glm::vec2(0.999958f, 1.0f - 0.336064f),
				glm::vec2(0.667979f, 1.0f - 0.335851f),
				glm::vec2(0.668104f, 1.0f - 0.000013f),
				glm::vec2(0.335973f, 1.0f - 0.335903f),
				glm::vec2(0.667979f, 1.0f - 0.335851f),
				glm::vec2(0.335973f, 1.0f - 0.335903f),
				glm::vec2(0.668104f, 1.0f - 0.000013f),
				glm::vec2(0.336098f, 1.0f - 0.000071f),
				glm::vec2(0.000103f, 1.0f - 0.336048f),
				glm::vec2(0.000004f, 1.0f - 0.671870f),
				glm::vec2(0.336024f, 1.0f - 0.671877f),
				glm::vec2(0.000103f, 1.0f - 0.336048f),
				glm::vec2(0.336024f, 1.0f - 0.671877f),
				glm::vec2(0.335973f, 1.0f - 0.335903f),
				glm::vec2(0.667969f, 1.0f - 0.671889f),
				glm::vec2(1.000004f, 1.0f - 0.671847f),
				glm::vec2(0.667979f, 1.0f - 0.335851f)
			};
			int _count = 0;
		};
	}
}