#include "GameObject.h"


/*
bool HMEngine::Core::GameObject::operator==(const GameObject& go)
{
	if (go._pos == this->_pos && go._vertices == this->_vertices)
		return true;
	return false;
}
*/

void HMEngine::Core::GameObject::SetPos(const HMEngine::Core::Transform & transform)
{
	*this->_transform = transform;
};
