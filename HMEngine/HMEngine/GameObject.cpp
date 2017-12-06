#include "GameObject.h"




void HMEngine::Core::GameObject::PlaceGameObject(glm::vec3 pos)
{
	this->_pos = pos;
}

bool HMEngine::Core::GameObject::operator==(const GameObject go)
{
	if (go._pos == this->_pos && go._vertices == this->_vertices)
		return true;
	return false;
}