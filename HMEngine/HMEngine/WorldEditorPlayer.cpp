#include "WorldEditorPlayer.h"
#include "WorldEditorPlayerComponent.h"

HMEngine::Core::WorldEditor::WorldEditorPlayer::WorldEditorPlayer(const std::string& playerName, float walkingSpeed, float runningSpeed) :
	HMEngine::Player(playerName, walkingSpeed, runningSpeed), 
	_worldEditorPlayerComponent(new HMEngine::Core::WorldEditor::WorldEditorPlayerComponent(*this->GetCameraController()))
{
	this->AddComponent(this->_worldEditorPlayerComponent);
}

HMEngine::Core::WorldEditor::WorldEditorPlayer::~WorldEditorPlayer()
{
}

HMEngine::Core::WorldEditor::WorldEditorPlayer::WorldEditorPlayer(const HMEngine::Core::WorldEditor::WorldEditorPlayer& other) : HMEngine::Player(other)
{
	this->_worldEditorPlayerComponent = new HMEngine::Core::WorldEditor::WorldEditorPlayerComponent(*other._worldEditorPlayerComponent);
}

HMEngine::Core::WorldEditor::WorldEditorPlayer& HMEngine::Core::WorldEditor::WorldEditorPlayer::operator=(const HMEngine::Core::WorldEditor::WorldEditorPlayer& other)
{
	if (this != &other)
	{
		HMEngine::Player::operator=(other);
		delete this->_worldEditorPlayerComponent;
		this->_worldEditorPlayerComponent = new HMEngine::Core::WorldEditor::WorldEditorPlayerComponent(*other._worldEditorPlayerComponent);
	}

	return *this;
}
