#include "CircleMovement.h"
#include "GameObject.h"
#include "Transform.h"

HMEngine::Components::CircleMovement::CircleMovement(float xCenter, float yCenter, float radius) : _circlePoints(), _i(0)
{
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

void HMEngine::Components::CircleMovement::UpdateEvent()
{
	this->_parentObject->GetTransform().SetPosition(this->_circlePoints[this->_i].first, 1, this->_circlePoints[this->_i].second);
	if (++this->_i > this->_circlePoints.size() - 1)
		this->_i = 0;
}