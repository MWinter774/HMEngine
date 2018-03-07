#include "WorldEditor.h"
#include "GameEngine.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Label.h"
#include "WorldEditorPlayer.h"


HMEngine::Core::WorldEditor::WorldEditor::WorldEditor(HMEngine::GameEngine& gameEngine) : _gameEngine(&gameEngine),
_player(new HMEngine::Core::WorldEditor::WorldEditorPlayer("WorldEditorPlayer", 100.0f, 200.0f))
{
}

HMEngine::Core::WorldEditor::WorldEditor::~WorldEditor()
{
}

HMEngine::Core::WorldEditor::WorldEditor::WorldEditor(const HMEngine::Core::WorldEditor::WorldEditor& other) : _gameEngine(other._gameEngine), 
_player(new HMEngine::Core::WorldEditor::WorldEditorPlayer(*other._player))
{
}

HMEngine::Core::WorldEditor::WorldEditor& HMEngine::Core::WorldEditor::WorldEditor::operator=(const HMEngine::Core::WorldEditor::WorldEditor& other)
{
	if (this != &other)
	{
		this->_gameEngine = other._gameEngine;
		this->_player = new HMEngine::Core::WorldEditor::WorldEditorPlayer(*other._player);
	}

	return *this;
}

void HMEngine::Core::WorldEditor::WorldEditor::Initialize()
{
	this->_gameEngine->EnableFPSCalculating();

	HMEngine::Core::GameObject testObject("test");
	testObject.AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/VeryNice.png"));
	this->_gameEngine->AddGameObject(testObject);

	this->_gameEngine->AddGameObject(this->_player);
}