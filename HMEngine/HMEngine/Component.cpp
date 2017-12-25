#include "Component.h"

void HMEngine::Components::Draw::Render()
{
	if (this->_parentObject != nullptr)
		this->_parentObject->Draw();
}