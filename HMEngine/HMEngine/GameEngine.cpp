#include "GameEngine.h"
float HMEngine::GameEngine::zNear = 0.1f;
float HMEngine::GameEngine::zFar = 1000.0f;
float HMEngine::GameEngine::fovInDegrees = 45.0f;
unsigned int HMEngine::GameEngine::windowWidth = 800U;
unsigned int HMEngine::GameEngine::windowHeight = 600U;




class Camera2
{
public:

	Camera2();
	Camera2(int screenWidth, int screenHeight);

	void SetViewport(int x, int y, int width, int height);
	glm::vec4 GetViewport() const;

	void SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar);

	void ApplyViewMatrix();

	void SetPosition(const glm::vec3& pos);
	glm::vec3 GetPosition() const;

	// Translate the Camera2 by some amount. If local is TRUE (default) then the translation should
	// be applied in the local-space of the Camera2. If local is FALSE, then the translation is 
	// applied in world-space.
	void Translate(const glm::vec3& delta, bool local = true);

	void SetRotation(const glm::quat& rot);
	glm::quat GetRotation() const;

	void SetEulerAngles(const glm::vec3& eulerAngles);
	glm::vec3 GetEulerAngles() const;

	// Rotate the Camera2 by some amount.
	void Rotate(const glm::quat& rot);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

protected:

	void UpdateViewMatrix();

	glm::vec4 m_Viewport;

	glm::vec3 m_Position;
	glm::quat m_Rotation;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

private:
	bool m_ViewDirty;
};

Camera2::Camera2()
	: m_Viewport(0)
	, m_Position(0)
	, m_Rotation()
	, m_ProjectionMatrix(1)
	, m_ViewMatrix(1)
	, m_ViewDirty(false)
{}

Camera2::Camera2(int screenWidth, int screenHeight)
	: m_Viewport(0, 0, screenWidth, screenHeight)
	, m_Position(0)
	, m_Rotation()
	, m_ProjectionMatrix(1)
	, m_ViewMatrix(1)
	, m_ViewDirty(false)
{

}

void Camera2::SetViewport(int x, int y, int width, int height)
{
	m_Viewport = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

glm::vec4 Camera2::GetViewport() const
{
	return m_Viewport;
}

void Camera2::SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}

void Camera2::ApplyViewMatrix()
{
	UpdateViewMatrix();
}

void Camera2::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
	m_ViewDirty = true;
}

glm::vec3 Camera2::GetPosition() const
{
	return m_Position;
}

void Camera2::Translate(const glm::vec3& delta, bool local /* = true */)
{
	if (local)
	{
		m_Position += m_Rotation * delta;
	}
	else
	{
		m_Position += delta;
	}
	m_ViewDirty = true;
}

void Camera2::SetRotation(const glm::quat& rot)
{
	m_Rotation = rot;
	m_ViewDirty = true;
}

glm::quat Camera2::GetRotation() const
{
	return m_Rotation;
}

void Camera2::SetEulerAngles(const glm::vec3& eulerAngles)
{
	m_Rotation = glm::quat(glm::radians(eulerAngles));
}

glm::vec3 Camera2::GetEulerAngles() const
{
	return glm::degrees(glm::eulerAngles(m_Rotation));
}

void Camera2::Rotate(const glm::quat& rot)
{
	m_Rotation = m_Rotation * rot;
	m_ViewDirty = true;
}

glm::mat4 Camera2::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 Camera2::GetViewMatrix()
{
	UpdateViewMatrix();
	return m_ViewMatrix;
}

void Camera2::UpdateViewMatrix()
{
	if (m_ViewDirty)
	{
		glm::mat4 translate = glm::translate(-m_Position);
		// Since we know the rotation matrix is orthonormalized, we can simply 
		// transpose the rotation matrix instead of inversing.
		glm::mat4 rotate = glm::transpose(glm::toMat4(m_Rotation));

		m_ViewMatrix = rotate * translate;

		m_ViewDirty = false;
	}
}




HMEngine::GameEngine::GameEngine() : _window(nullptr)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) //try to initialize SDL
	{
		std::cout << "SDL INITIALIZATION FAILED!" << std::endl;
		system("pause");
		return;
	}
	std::cout << "Succeeded initializing SDL..." << std::endl;
}

HMEngine::GameEngine::~GameEngine()
{
	if (this->_window != nullptr)
		delete this->_window;
	SDL_Quit();
}

void HMEngine::GameEngine::CreateNewWindow(int width, int height, const std::string& title, bool fullscreen)
{
	HMEngine::GameEngine::windowWidth = width;
	HMEngine::GameEngine::windowHeight = height;
	HMEngine::Core::Transform::UpdateProjectionMatrix();
	_window = new HMEngine::Core::Rendering::Window(width, height, title, fullscreen);
}

void HMEngine::GameEngine::SetFov(float fovInDegrees)
{
	HMEngine::Core::Transform::UpdateProjectionMatrix(); HMEngine::GameEngine::fovInDegrees = fovInDegrees;
}

void HMEngine::GameEngine::SetZNear(float zNear)
{
	HMEngine::Core::Transform::UpdateProjectionMatrix(); HMEngine::GameEngine::zNear = zNear;
}

void HMEngine::GameEngine::SetZFar(float zFar)
{
	HMEngine::Core::Transform::UpdateProjectionMatrix(); HMEngine::GameEngine::zFar = zFar;
}

/*
Runs the game.
*/


void HMEngine::GameEngine::Run(HMEngine::Core::Rendering::Shaders::BasicShader _shader)
{
	int count = 0;

	GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}
	else
	{
		std::string vs = "..\\Debug\\basicShaderVs.txt";
		std::string fs = "..\\Debug\\basicShaderFs.txt";


		GLuint vertexShader = HMEngine::Core::Rendering::Shaders::BasicShader::LoadShader(GL_VERTEX_SHADER, vs);
		GLuint fragmentShader = HMEngine::Core::Rendering::Shaders::BasicShader::LoadShader(GL_FRAGMENT_SHADER, fs);

		std::vector<GLuint> shaders;
		shaders.push_back(vertexShader);
		shaders.push_back(fragmentShader);

		GLuint shaderProgram = HMEngine::Core::Rendering::Shaders::BasicShader::CreateShaderProgram(shaders);

		Camera2 g_Camera;
		glm::vec3 g_InitialCameraPosition;
		glm::quat g_InitialCameraRotation;

		g_InitialCameraPosition = glm::vec3(0, 0, 10);
		g_Camera.SetPosition(g_InitialCameraPosition);
		g_Camera.SetRotation(g_InitialCameraRotation);
		int w = 800, h = 600;

		g_Camera.SetViewport(0, 0, w, h);
		g_Camera.SetProjectionRH(60.0f, w / (float)h, 0.1f, 100.0f);
		glm::quat g_Rotation;
		glm::mat4 mvp = g_Camera.GetProjectionMatrix() * g_Camera.GetViewMatrix() * glm::toMat4(g_Rotation);


		while (!HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDLK_ESCAPE)) //temp
		{
			HMEngine::Core::Hardware::HardwareInputs::Update();

			if (HMEngine::Core::Hardware::HardwareInputs::IsKeyTapped(SDLK_w))
				std::cout << "w key is tapped" << std::endl;
			if (HMEngine::Core::Hardware::HardwareInputs::IsKeyDown(SDLK_s))
				std::cout << "s key is held down" << std::endl;
			if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonDown(SDL_BUTTON_LEFT))
				std::cout << "left mouse button is held down" << std::endl;
			if (HMEngine::Core::Hardware::HardwareInputs::IsMouseButtonTapped(SDL_BUTTON_RIGHT))
				std::cout << "right mouse button is tapped" << std::endl;
			if (count % 500000 == 0)
			{
				std::cout << HMEngine::Core::Hardware::HardwareInputs::GetCursorXPos() << ", " << HMEngine::Core::Hardware::HardwareInputs::GetCursorYPos() << std::endl;
				count = 0;
			}
			count++;

			this->_window->Update(shaderProgram, (this->_gameObjects), mvp);

		}
	}
}

void HMEngine::GameEngine::AddGameObject(const HMEngine::Core::GameObject& gameObject)
{ 
	this->_gameObjects.push_back(gameObject); 
}

/*
void HMEngine::GameEngine::RemoveGameObject(const HMEngine::Core::GameObject& gameObject)
{
	this->_gameObjects.erase(std::remove(this->_gameObjects.begin(), this->_gameObjects.end(), gameObject), this->_gameObjects.end());
}
*/