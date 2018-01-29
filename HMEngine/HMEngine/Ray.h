#pragma once
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			class Ray
			{
			public:
				Ray(const glm::vec3& origin, const glm::vec3& direction);
				~Ray();

				inline glm::vec3 GetOrigin() const { return this->_origin; }
				inline glm::vec3 GetDirection() const { return this->_direction; }

				inline void SetOrigin(const glm::vec3& origin) { this->_origin = origin; }
				inline void SetDirection(const glm::vec3& direction) { this->_direction = direction; }

			private:
				glm::vec3 _origin;
				glm::vec3 _direction;
			};
		}
	}
}