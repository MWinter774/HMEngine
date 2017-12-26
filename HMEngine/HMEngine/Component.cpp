#include "Component.h"

/*
calls the draw function of the gameObject
*/
void HMEngine::Components::Draw::Render()
{
	if (this->_parentObject != nullptr)
		this->_parentObject->Draw();
}