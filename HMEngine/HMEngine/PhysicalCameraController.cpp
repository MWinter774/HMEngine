#include "PhysicalCameraController.h"
#include "Camera.h"
#include "SDL2.0.7\SDL.h"
#include "HardwareInputs.h"
#include "GameSettings.h"
#include "GameObject.h"
#include "Transform.h"

HMEngine::Components::PhysicalCameraController::PhysicalCameraController(float walkingSpeed, float runningSpeed) : _camera(&HMEngine::Core::Rendering::Camera::GetInstance()),
_movementSpeed(walkingSpeed), _walkingSpeed(walkingSpeed), _runningSpeed(runningSpeed), _isActive(true), _movement(new MovementData()),
_right(), _forward(), _up(), _horizontalAngle(float(M_PI)), _verticalAngle(0.0f)
{
	this->InitializeEvents<PhysicalCameraController>(this);
}

HMEngine::Components::PhysicalCameraController::~PhysicalCameraController()
{
	delete this->_movement;
}

HMEngine::Components::PhysicalCameraController::PhysicalCameraController(const HMEngine::Components::PhysicalCameraController& other) : _camera(other._camera),
_movementSpeed(other._walkingSpeed), _walkingSpeed(other._walkingSpeed), _runningSpeed(other._runningSpeed), _isActive(true),
_right(other._right), _forward(other._forward), _up(other._up), _movement(new MovementData(*other._movement)),
_horizontalAngle(other._horizontalAngle), _verticalAngle(other._verticalAngle)
{
	this->InitializeEvents<PhysicalCameraController>(this);
}

HMEngine::Components::PhysicalCameraController& HMEngine::Components::PhysicalCameraController::operator=(const HMEngine::Components::PhysicalCameraController& other)
{
	if (this != &other)
	{
		this->InitializeEvents<PhysicalCameraController>(this);

		delete this->_movement;

		this->_movement = new MovementData(*other._movement);
		this->_camera = other._camera;
		this->_movementSpeed = other._walkingSpeed;
		this->_walkingSpeed = other._walkingSpeed;
		this->_runningSpeed = other._runningSpeed;
		this->_isActive = true;
		this->_right = other._right;
		this->_forward = other._forward;
		this->_up = other._up;
		this->_horizontalAngle = other._horizontalAngle;
		this->_verticalAngle = other._verticalAngle;
	}

	return *this;
}

void HMEngine::Components::PhysicalCameraController::UpdateEvent()
{
	if (this->_isActive)
	{
		int cursorXPos = HMEngine::Core::Hardware::HardwareInputs::GetCursorXPos(), cursorYPos = HMEngine::Core::Hardware::HardwareInputs::GetCursorYPos();
		double delta = 0.01;

		this->_horizontalAngle += HMEngine::GameSettings::GetSensitivity() * float(int(HMEngine::GameSettings::GetWindowWidth()) / 2.0f - cursorXPos);
		this->_verticalAngle += HMEngine::GameSettings::GetSensitivity() * float(int(HMEngine::GameSettings::GetWindowHeight()) / 2.0f - cursorYPos);

		this->_forward = glm::vec3(cos(_verticalAngle) * sin(_horizontalAngle), sin(_verticalAngle), cos(_verticalAngle) * cos(_horizontalAngle));
		this->_right = glm::vec3(sin(this->_horizontalAngle - M_PI / 2.0f), 0, cos(this->_horizontalAngle - M_PI / 2.0f));
		this->_up = glm::cross(this->_right, this->_forward);

		this->_camera->SetForawrd(this->_forward);

		this->_camera->SetRight(this->_right);

		this->_camera->SetUp(this->_up);

		/*if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_LSHIFT))
		{
			this->_movementSpeed = this->_runningSpeed;
		}
		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_W))
		{
			this->Move(this->_forward, float(delta) * this->_movementSpeed);
			this->_movement->forward = true;
		}
		else
		{
			this->_movement->forward = false;
		}

		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_S))
		{
			this->Move(this->_forward, float(delta) * -this->_movementSpeed);
			this->_movement->backward = true;
		}
		else
		{
			this->_movement->backward = false;
		}

		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_A))
		{
			this->Move(this->_right, float(delta) * -this->_movementSpeed);
			this->_movement->left = true;
		}
		else
		{
			this->_movement->left = false;
		}

		if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDL_SCANCODE_D))
		{
			this->Move(this->_right, float(delta) * this->_movementSpeed);
			this->_movement->right = true;
		}
		else
		{
			this->_movement->right = false;
		}

		this->_movementSpeed = this->_walkingSpeed;*/
	}
}

void HMEngine::Components::PhysicalCameraController::Move(const glm::vec3& direction, float amount) const
{
	//this->_camera->AddPosition(direction * amount);
	//this->_parentObject->GetTransform().AddPosition(direction * amount);
}