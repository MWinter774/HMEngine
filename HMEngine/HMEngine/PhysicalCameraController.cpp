#include "PhysicalCameraController.h"
#include "Camera.h"
#include "SDL2.0.7\SDL.h"
#include "HardwareInputs.h"
#include "GameSettings.h"
#include "GameObject.h"
#include "Transform.h"

HMEngine::Components::PhysicalCameraController::PhysicalCameraController() : _camera(&HMEngine::Core::Rendering::Camera::GetInstance()),
_isActive(true), _right(), _forward(), _up(), _horizontalAngle(float(M_PI)), _verticalAngle(0.0f)
{
	this->InitializeEvents<PhysicalCameraController>(this);
}

HMEngine::Components::PhysicalCameraController::~PhysicalCameraController()
{
}

HMEngine::Components::PhysicalCameraController::PhysicalCameraController(const HMEngine::Components::PhysicalCameraController& other) : _camera(other._camera),
_isActive(true), _right(other._right), _forward(other._forward), _up(other._up), _horizontalAngle(other._horizontalAngle), _verticalAngle(other._verticalAngle)
{
	this->InitializeEvents<PhysicalCameraController>(this);
}

HMEngine::Components::PhysicalCameraController& HMEngine::Components::PhysicalCameraController::operator=(const HMEngine::Components::PhysicalCameraController& other)
{
	if (this != &other)
	{
		this->InitializeEvents<PhysicalCameraController>(this);

		this->_camera = other._camera;
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
	}
}