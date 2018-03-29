#include "EnemyBot.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "BoundingSphere.h"
#include "BrainComponent.h"
#include "Billboard.h"
#include "ProgressBar.h"
#include "GameEngine.h"

EnemyBot::EnemyBot(const std::string& name, const glm::vec3& position, HMEngine::PhysicalPlayer* player, const std::string& gnnFilePath) :
	HMEngine::Core::GameObject(name), _player(player), _forward(0, 0, 1), _gnnFilePath(gnnFilePath)
{
	this->InitializeEvents<EnemyBot>(this);
	this->GetTransform().SetPosition(position);
	this->GetTransform().SetScale(2, 2, 2);
	//this->GetTransform().SetScaleZ(1.5f);
	//this->GetTransform().SetRotationX(1.57f);
	this->_projectionMatrix = glm::perspective(glm::radians(45.0f),
		HMEngine::GameSettings::GetWindowWidth() / (float)HMEngine::GameSettings::GetWindowHeight(), 0.1f, 1000.0f);
	this->_viewMatrix = glm::lookAt(position, position + glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
}

EnemyBot::~EnemyBot()
{
}

void EnemyBot::UpdateEvent()
{
	auto newPos = this->GetTransform().GetPosition() += glm::vec3(0, 3, 0);
	this->_health->SetPosition(newPos);
	for (auto& child : this->_health->GetChilds())
		child->SetPosition(newPos);
	this->GetTransform().LookAt(this->_player->GetTransform().GetPosition());
	this->_collider->SetRotation(this->GetTransform().GetRotationQuat());
	this->_forward = this->GetTransform().GetRotationQuat() * this->_forward;
}

void EnemyBot::AttachToGameEngineEvent()
{
	this->_mesh = new HMEngine::Components::MeshRenderer("./resources/objects/monkey.obj", "./resources/textures/mud.png");
	if (this->_gnnFilePath != "")
		this->_brain = new HMEngine::Components::BrainComponent(*this->_player, this->_gnnFilePath);
	else
		this->_brain = new HMEngine::Components::BrainComponent(*this->_player);
	this->_collider = new HMEngine::Core::Physics::Colliders::BoundingSphere(10.0f);
	this->_health = new HMEngine::UI::ProgressBar(this->GetName() + "_health", glm::vec2(), glm::vec2(5, 1), "./resources/UITextures/progressBarBackground.png",
		"./resources/UITextures/progressBarBarTexture.png", 100);
	this->_healthBar = new HMEngine::UI::Billboard(this->GetName() + "_healthBar", this->GetTransform().GetPosition() += glm::vec3(0, 2, 0), this->_health);
	this->AddComponent(this->_mesh);
	this->AddComponent(this->_brain);
	this->AddComponent(this->_collider);
	this->GetGameEngine().AddUI(this->_healthBar);
	this->InitializeEventObject();
}

bool EnemyBot::GotHit(float damageInPercentage)
{
	this->_health->DecreaseBar(damageInPercentage);

	return this->_health->GetPercentage() <= 0.0f; //Returns whether the bot is dead
}

void EnemyBot::SetPosition(const glm::vec3& position)
{
	this->_collider->SetPosition(position);
	this->GetTransform().SetPosition(position);
	auto newPos = position + glm::vec3(0, 3, 0);
	this->_health->SetPosition(newPos);
	for (auto& child : this->_health->GetChilds())
		child->SetPosition(newPos);
}

void EnemyBot::AddPosition(const glm::vec3& translation)
{
	auto position = this->GetTransform().GetPosition() + translation;
	this->_collider->SetPosition(position);
	this->GetTransform().SetPosition(position);
	auto newPos = position + glm::vec3(0, 3, 0);
	this->_health->SetPosition(newPos);
	for (auto& child : this->_health->GetChilds())
		child->SetPosition(newPos);
}

void EnemyBot::SetHealth(float health)
{
	this->_health->SetPercentage(health);
}

bool EnemyBot::Shoot()
{
	glm::vec3 position = this->GetTransform().GetPosition();
	this->_viewMatrix = glm::lookAt(position, position + this->_forward, glm::vec3(0, 1, 0));
	glm::mat4 translationMatrix = this->_player->GetTransform().GetTranslationMatrix();
	glm::mat4 MVP = this->_projectionMatrix * this->_viewMatrix * translationMatrix;

	return EnemyBot::IsObjectVisible(MVP, this->_player->GetTransform().GetPosition(), 0.5f);
}

void EnemyBot::Lost()
{
	this->_brain->Lost();
}

bool EnemyBot::IsObjectVisible(const glm::mat4& objectMVPMatrix, const glm::vec3& objectPos, float radius)
{
	GLfloat xPos = objectPos.x, yPos = objectPos.y, zPos = objectPos.z;
	const GLfloat* MVPMatrix = glm::value_ptr(objectMVPMatrix);
	GLfloat leftPlane[4];
	GLfloat rightPlane[4];
	GLfloat bottomPlane[4];
	GLfloat nearPlane[4];
	GLfloat topPlane[4];
	GLfloat farPlane[4];
	GLfloat length;
	GLfloat distance;

	leftPlane[A] = MVPMatrix[3] + MVPMatrix[0];
	leftPlane[B] = MVPMatrix[7] + MVPMatrix[4];
	leftPlane[C] = MVPMatrix[11] + MVPMatrix[8];
	leftPlane[D] = MVPMatrix[15] + MVPMatrix[12];

	/* Normalize the plane */
	length = sqrtf(leftPlane[A] * leftPlane[A] + leftPlane[B] * leftPlane[B] + leftPlane[C] * leftPlane[C]);
	leftPlane[A] /= length;
	leftPlane[B] /= length;
	leftPlane[C] /= length;
	leftPlane[D] /= length;

	/* Check the point's location with respect to the left plane of viewing frustrum */
	distance = leftPlane[A] * xPos + leftPlane[B] * yPos + leftPlane[C] * zPos + leftPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the left plane

					  /* Check the point's location with respect to the right plane of viewing frustum */
	rightPlane[A] = MVPMatrix[3] - MVPMatrix[0];
	rightPlane[B] = MVPMatrix[7] - MVPMatrix[4];
	rightPlane[C] = MVPMatrix[11] - MVPMatrix[8];
	rightPlane[D] = MVPMatrix[15] - MVPMatrix[12];

	/* Normalize the plane */
	length = sqrtf(rightPlane[A] * rightPlane[A] + rightPlane[B] * rightPlane[B] + rightPlane[C] * rightPlane[C]);
	rightPlane[A] /= length;
	rightPlane[B] /= length;
	rightPlane[C] /= length;
	rightPlane[D] /= length;

	distance = rightPlane[A] * xPos + rightPlane[B] * yPos + rightPlane[C] * zPos + rightPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the right plane

					  /* Check the point's location with respect to the bottom plane of viewing frustum */
	bottomPlane[A] = MVPMatrix[3] + MVPMatrix[1];
	bottomPlane[B] = MVPMatrix[7] + MVPMatrix[5];
	bottomPlane[C] = MVPMatrix[11] + MVPMatrix[9];
	bottomPlane[D] = MVPMatrix[15] + MVPMatrix[13];

	/* Normalize the plane */
	length = sqrtf(bottomPlane[A] * bottomPlane[A] + bottomPlane[B] * bottomPlane[B] + bottomPlane[C] * bottomPlane[C]);
	bottomPlane[A] /= length;
	bottomPlane[B] /= length;
	bottomPlane[C] /= length;
	bottomPlane[D] /= length;

	distance = bottomPlane[A] * xPos + bottomPlane[B] * yPos + bottomPlane[C] * zPos + bottomPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the bottom plane

					  /* Check the point's location with respect to the top plane of viewing frustrum */
	topPlane[A] = MVPMatrix[3] - MVPMatrix[1];
	topPlane[B] = MVPMatrix[7] - MVPMatrix[5];
	topPlane[C] = MVPMatrix[11] - MVPMatrix[9];
	topPlane[D] = MVPMatrix[15] - MVPMatrix[13];

	/* Normalize the plane */
	length = sqrtf(topPlane[A] * topPlane[A] + topPlane[B] * topPlane[B] + topPlane[C] * topPlane[C]);
	topPlane[A] /= length;
	topPlane[B] /= length;
	topPlane[C] /= length;
	topPlane[D] /= length;

	distance = topPlane[A] * xPos + topPlane[B] * yPos + topPlane[C] * zPos + topPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the top plane

					  /* Check the point's location with respect to the near plane of viewing frustum */
	nearPlane[A] = MVPMatrix[3] + MVPMatrix[2];
	nearPlane[B] = MVPMatrix[7] + MVPMatrix[6];
	nearPlane[C] = MVPMatrix[11] + MVPMatrix[10];
	nearPlane[D] = MVPMatrix[15] + MVPMatrix[14];

	/* Normalize the plane */
	length = sqrtf(nearPlane[A] * nearPlane[A] + nearPlane[B] * nearPlane[B] + nearPlane[C] * nearPlane[C]);
	nearPlane[A] /= length;
	nearPlane[B] /= length;
	nearPlane[C] /= length;
	nearPlane[D] /= length;

	distance = nearPlane[A] * xPos + nearPlane[B] * yPos + nearPlane[C] * zPos + nearPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is completely outside the near plane

					  /* Check the point's location with respect to the far plane of viewing frustum */
	farPlane[A] = MVPMatrix[3] - MVPMatrix[2];
	farPlane[B] = MVPMatrix[7] - MVPMatrix[6];
	farPlane[C] = MVPMatrix[11] - MVPMatrix[10];
	farPlane[D] = MVPMatrix[15] - MVPMatrix[14];

	/* Normalize the plane */
	length = sqrtf(farPlane[A] * farPlane[A] + farPlane[B] * farPlane[B] + farPlane[C] * farPlane[C]);
	farPlane[A] /= length;
	farPlane[B] /= length;
	farPlane[C] /= length;
	farPlane[D] /= length;

	distance = farPlane[A] * xPos + farPlane[B] * yPos + farPlane[C] * zPos + farPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the far plane

	/* The bounding sphere is within at least all six sides of the view frustum, so it's visible */
	return true;
}
