#include "BoundingSphere.h"
#include "IntersectionData.h"

HMEngine::Core::Physics::BoundingSphere::BoundingSphere(const std::vector<glm::vec3>& vertices) : _points()
{
	std::vector<float> coords;
	for (auto& vertex : vertices)
	{
		coords.push_back(vertex.x);
		coords.push_back(vertex.y);
		coords.push_back(vertex.z);

		this->_points.push_back(Seb::Point<float>(3, coords.begin()));

		coords.clear();
	}
	this->_miniball = new Seb::Smallest_enclosing_ball<float>(3, this->_points);
	this->_radius = this->_miniball->radius();

	/* Initializes the center */
	float tempCenter[3] = { 0.0f };
	float* centerBegin = this->_miniball->center_begin();
	float* centerEnd = this->_miniball->center_end();
	for (unsigned int i = 0; i < 3 && centerBegin != centerEnd; i++)
	{
		tempCenter[i] = *centerBegin++;
	}
	this->_center = glm::vec3(tempCenter[0], tempCenter[1], tempCenter[2]);
}

HMEngine::Core::Physics::BoundingSphere::BoundingSphere(const glm::vec3& center, float radius) : _center(center), _radius(radius)
{
}

HMEngine::Core::Physics::BoundingSphere::~BoundingSphere()
{
	if (this->_miniball != nullptr)
		delete this->_miniball;
}

HMEngine::Core::Physics::BoundingSphere::BoundingSphere(const HMEngine::Core::Physics::BoundingSphere& other) : _radius(other._radius), _center(other._center)
{
	if (other._miniball != nullptr)
	{
		this->_points = other._points;
		this->_miniball = new Seb::Smallest_enclosing_ball<float>(3, this->_points);
	}
}

HMEngine::Core::Physics::BoundingSphere& HMEngine::Core::Physics::BoundingSphere::operator=(const HMEngine::Core::Physics::BoundingSphere& other)
{
	if (this != &other)
	{
		this->_radius = other._radius;
		this->_center = other._center;
		if (other._miniball != nullptr)
		{
			this->_points = other._points;
			this->_miniball = new Seb::Smallest_enclosing_ball<float>(3, this->_points);
		}
	}

	return *this;
}

HMEngine::Core::Physics::IntersectionData HMEngine::Core::Physics::BoundingSphere::IsIntersect(const HMEngine::Core::Physics::BoundingSphere& other)
{
	float radiusDistance = this->_radius + other._radius; //distance between centers if the spheres are touching
	float centerDistance = float((other._center - this->_center).length()); //distance between sphere's centers

	return HMEngine::Core::Physics::IntersectionData(centerDistance < radiusDistance, centerDistance - radiusDistance);
}