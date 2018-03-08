#include "QuadCollection.h"

HMEngine::UI::QuadCollection::QuadCollection(const std::string& name, const glm::vec2& position, const glm::vec2& scale) :
	HMEngine::UI::Quad(name, position, scale)
{
	this->InitializeEvents<QuadCollection>(this);
}

HMEngine::UI::QuadCollection::~QuadCollection()
{
}

HMEngine::UI::QuadCollection::QuadCollection(const HMEngine::UI::QuadCollection& other) : HMEngine::UI::Quad(other)
{
	this->InitializeEvents<QuadCollection>(this);
}

HMEngine::UI::QuadCollection& HMEngine::UI::QuadCollection::operator=(const HMEngine::UI::QuadCollection& other)
{
	if (this != &other)
	{
		this->InitializeEvents<QuadCollection>(this);
		HMEngine::UI::Quad::operator=(other);
	}

	return *this;
}

void HMEngine::UI::QuadCollection::AddQuad(const HMEngine::UI::Quad& quadToAdd)
{
	HMEngine::UI::Quad* quadClone = quadToAdd.Clone();
	this->AddChild(quadClone);
	this->_quads.push_back(quadClone);
}

void HMEngine::UI::QuadCollection::AddQuad(HMEngine::UI::Quad* quadToAdd)
{
	this->AddChild(quadToAdd);
	this->_quads.push_back(quadToAdd);
}