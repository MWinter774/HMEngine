#include "CircleMovement.h"
#include "GameObject.h"
#include "Transform.h"

HMEngine::Components::CircleMovement::CircleMovement(float xCenter, float yCenter, float radius) : _circlePoints(), _i(0)
{
	this->InitializeEvents<CircleMovement>(this);
	for (float i = -180; i < 180; i += 0.03f)
	{
		float x = xCenter + cos(i) * radius;
		float y = yCenter + sin(i) * radius;
		this->_circlePoints.push_back(std::pair<float, float>(x, y));
	}
}

HMEngine::Components::CircleMovement::~CircleMovement()
{
}

HMEngine::Components::CircleMovement::CircleMovement(const HMEngine::Components::CircleMovement& other) : _circlePoints(other._circlePoints), _i(other._i)
{
	this->InitializeEvents<CircleMovement>(this);
}

HMEngine::Components::CircleMovement& HMEngine::Components::CircleMovement::operator=(const HMEngine::Components::CircleMovement& other)
{
	if (this != &other)
	{
		this->_circlePoints = other._circlePoints;
		this->_i = other._i;
		this->InitializeEvents<CircleMovement>(this);
	}

	return *this;
}

void HMEngine::Components::CircleMovement::UpdateEvent()
{
	this->_parentObject->GetTransform().SetPosition(this->_circlePoints[this->_i].first, 1, this->_circlePoints[this->_i].second);
	if (++this->_i > this->_circlePoints.size() - 1)
		this->_i = 0;
}