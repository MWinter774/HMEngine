#include "CameraController.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "HardwareInputs.h"
#include "GameSettings.h"

HMEngine::Components::CameraController::CameraController() : _camera(HMEngine::Core::Rendering::Camera::GetInstance()), _horizontalAngle(float(M_PI)), _verticalAngle(0.0f), _right(), _forward(), _up(), _movementSpeed(20.0f)
{
}

HMEngine::Components::CameraController::~CameraController()
{
}

void HMEngine::Components::CameraController::UpdateEvent()
{
	//this->_parentObject->GetTransform().SetPosition(this->_camera.GetPosition());

	int cursorXPos = HMEngine::Core::Hardware::HardwareInputs::GetCursorXPos(), cursorYPos = HMEngine::Core::Hardware::HardwareInputs::GetCursorYPos();
	double delta = 0.01;

	this->_horizontalAngle += HMEngine::GameSettings::GetSensitivity() * float(int(HMEngine::GameSettings::GetWindowWidth()) / 2 - cursorXPos);
	this->_verticalAngle += HMEngine::GameSettings::GetSensitivity() * float(int(HMEngine::GameSettings::GetWindowHeight()) / 2 - cursorYPos);

	this->_forward = glm::vec3(cos(_verticalAngle) * sin(_horizontalAngle), sin(_verticalAngle), cos(_verticalAngle) * cos(_horizontalAngle));
	this->_right = glm::vec3(sin(this->_horizontalAngle - M_PI / 2.0f), 0, cos(this->_horizontalAngle - M_PI / 2.0f));
	this->_up = glm::cross(this->_right, this->_forward);

	this->_camera.SetForawrd(this->_forward);
	
	this->_camera.SetRight(this->_right);

	this->_camera.SetUp(this->_up);

	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_LSHIFT))
	{
		this->_movementSpeed = 10.0f;
	}
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_W))
	{
		this->Move(this->_forward, float(delta) * this->_movementSpeed);
	}
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_S))
	{
		this->Move(this->_forward, float(delta) * -this->_movementSpeed);
	}
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_A))
	{
		this->Move(this->_right, float(delta) * -this->_movementSpeed);
	}
	if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_D))
	{
		this->Move(this->_right, float(delta) * this->_movementSpeed);
	}
	this->_movementSpeed = 50.0f;
}

void HMEngine::Components::CameraController::Move(const glm::vec3& direction, float amount) const
{
	this->_camera.AddPosition(direction * amount);
}
