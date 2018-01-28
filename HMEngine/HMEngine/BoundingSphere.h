#pragma once
#include <glm\glm.hpp>
#include <vector>
#include "Seb\Seb.h"

namespace HMEngine
{
	namespace Core
	{
		namespace Physics
		{
			class IntersectionData;

			class BoundingSphere
			{
			public:
				BoundingSphere(const std::vector<glm::vec3>& vertices);
				BoundingSphere(const glm::vec3& center, float radius);
				~BoundingSphere();
				BoundingSphere(const HMEngine::Core::Physics::BoundingSphere& other);
				HMEngine::Core::Physics::BoundingSphere& operator=(const HMEngine::Core::Physics::BoundingSphere& other);

				HMEngine::Core::Physics::IntersectionData IsIntersect(const HMEngine::Core::Physics::BoundingSphere& other);

				inline glm::vec3 GetCenter() const { return this->_center; }
				inline float GetRadius() const { return this->_radius; }

			private:
				Seb::Smallest_enclosing_ball<float>* _miniball;
				std::vector<Seb::Point<float>> _points;
				glm::vec3 _center;
				float _radius;
			};
		}
	}
}