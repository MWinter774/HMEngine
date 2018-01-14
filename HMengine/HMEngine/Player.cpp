#include "Player.h"
#include "MeshRenderer.h"
#include "CameraController.h"
#include "RenderingEngine.h" //DEBUG

std::vector<glm::vec3> vertices = //DEBUG
{
	glm::vec3(1,  1,  1),
	glm::vec3(-1,  1,  1),
	glm::vec3(-1, -1,  1),
	glm::vec3(1, -1,  1),
	glm::vec3(1, -1, -1),
	glm::vec3(-1, -1, -1),
	glm::vec3(-1,  1, -1),
	glm::vec3(1,  1, -1),
};
std::vector<GLuint> indices = //DEBUG
{
	0, 1, 2, 2, 3, 0,           // Front face
	7, 4, 5, 5, 6, 7,           // Back face
	6, 5, 2, 2, 1, 6,           // Left face
	7, 0, 3, 3, 4, 7,           // Right face
	7, 6, 1, 1, 0, 7,           // Top face
	3, 2, 5, 5, 4, 3            // Bottom face
};

std::vector<glm::vec2> uvs = { //DEBUG
	glm::vec2(0.000059f, 1.0f - 0.000004f),
	glm::vec2(0.000103f, 1.0f - 0.336048f),
	glm::vec2(0.335973f, 1.0f - 0.335903f),
	glm::vec2(1.000023f, 1.0f - 0.000013f),
	glm::vec2(0.667979f, 1.0f - 0.335851f),
	glm::vec2(0.999958f, 1.0f - 0.336064f),
	glm::vec2(0.667979f, 1.0f - 0.335851f),
	glm::vec2(0.336024f, 1.0f - 0.671877f),
	glm::vec2(0.667969f, 1.0f - 0.671889f),
	glm::vec2(1.000023f, 1.0f - 0.000013f),
	glm::vec2(0.668104f, 1.0f - 0.000013f),
	glm::vec2(0.667979f, 1.0f - 0.335851f),
	glm::vec2(0.000059f, 1.0f - 0.000004f),
	glm::vec2(0.335973f, 1.0f - 0.335903f),
	glm::vec2(0.336098f, 1.0f - 0.000071f),
	glm::vec2(0.667979f, 1.0f - 0.335851f),
	glm::vec2(0.335973f, 1.0f - 0.335903f),
	glm::vec2(0.336024f, 1.0f - 0.671877f)
};

HMEngine::Player::Player(const std::string& playerName) : GameObject(playerName), _meshRenderer(new HMEngine::Components::MeshRenderer(vertices, indices, uvs, "./resources/textures/bricks.png")), _cameraController(new HMEngine::Components::CameraController())
{
	//this->AddComponent(*this->_meshRenderer);
	this->AddComponent(*this->_cameraController);
}

HMEngine::Player::~Player()
{
	delete this->_meshRenderer;
	delete this->_cameraController;
}

HMEngine::Player::Player(const HMEngine::Player& other) : GameObject(other), _meshRenderer(new HMEngine::Components::MeshRenderer(*other._meshRenderer)), _cameraController(new HMEngine::Components::CameraController(*other._cameraController))
{
}

HMEngine::Player& HMEngine::Player::operator=(const HMEngine::Player& other)
{
	if (this != &other)
	{
		delete this->_meshRenderer;
		this->_meshRenderer = new HMEngine::Components::MeshRenderer(*other._meshRenderer);
		delete this->_cameraController;
		this->_cameraController = new HMEngine::Components::CameraController(*other._cameraController);
	}

	return *this;
}
