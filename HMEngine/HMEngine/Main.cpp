#include "HMEngineIncludes.h"
#include "GameObject.h"
#include "GameEngine.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Player.h"
#include "Transform.h"
#include "Utilities.h"
#include "DebugComponent.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "CircleMovement.h"
#include "Terrain.h"
#include "Image.h"
#include "Button.h"
#include "Font.h"
#include <string>
#include "OpenGLObject.h"
#include "OpenGLQuad.h"
#include <variant>

int main()
{
	/*
	std::string title = "HMEngine";

	HMEngine::GameEngine g;
	g.CreateNewWindow(800, 600, title, false);

	//create cube
	std::vector<glm::vec3> vertices =
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
	std::vector<GLuint> indices =
	{
		0, 1, 2, 2, 3, 0,           // Front face
		7, 4, 5, 5, 6, 7,           // Back face
		6, 5, 2, 2, 1, 6,           // Left face
		7, 0, 3, 3, 4, 7,           // Right face
		7, 6, 1, 1, 0, 7,           // Top face
		3, 2, 5, 5, 4, 3            // Bottom face
	};

	std::vector<glm::vec2> uvs = {
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
		glm::vec2(0.336024f, 1.0f - 0.671877f),
		glm::vec2(1.000004f, 1.0f - 0.671847f),
		glm::vec2(0.999958f, 1.0f - 0.336064f),
		glm::vec2(0.667979f, 1.0f - 0.335851f),
		glm::vec2(0.668104f, 1.0f - 0.000013f),
		glm::vec2(0.335973f, 1.0f - 0.335903f),
		glm::vec2(0.667979f, 1.0f - 0.335851f),
		glm::vec2(0.335973f, 1.0f - 0.335903f),
		glm::vec2(0.668104f, 1.0f - 0.000013f),
		glm::vec2(0.336098f, 1.0f - 0.000071f),
		glm::vec2(0.000103f, 1.0f - 0.336048f),
		glm::vec2(0.000004f, 1.0f - 0.671870f),
		glm::vec2(0.336024f, 1.0f - 0.671877f),
		glm::vec2(0.000103f, 1.0f - 0.336048f),
		glm::vec2(0.336024f, 1.0f - 0.671877f),
		glm::vec2(0.335973f, 1.0f - 0.335903f),
		glm::vec2(0.667969f, 1.0f - 0.671889f),
		glm::vec2(1.000004f, 1.0f - 0.671847f),
		glm::vec2(0.667979f, 1.0f - 0.335851f)
	};

	std::vector<glm::vec3> normals = {
		glm::vec3(-1.0f, 0.0f, 0.0f), // Left Side
		glm::vec3(0.0f, 0.0f, -1.0f), // Back Side
		glm::vec3(0.0f,-1.0f, 0.0f), // Bottom Side
		glm::vec3(0.0f, 0.0f, -1.0f), // Back Side
		glm::vec3(-1.0f, 0.0f, 0.0f), // Left Side
		glm::vec3(0.0f, -1.0f, 0.0f), // Bottom Side
		glm::vec3(0.0f, 0.0f, 1.0f), // front Side
		glm::vec3(1.0f, 0.0f, 0.0f), // right Side
		glm::vec3(1.0f, 0.0f, 0.0f), // right Side
		glm::vec3(0.0f, 1.0f, 0.0f),// top Side
		glm::vec3(0.0f, 1.0f, 0.0f), // top Side
		glm::vec3(0.0f, 0.0f, 1.0f) // front Side

	};

	//HMEngine::GameSettings::CalculateFPS(true);

	HMEngine::Core::GameObject gameMaster("master");
	gameMaster.AddComponent(HMEngine::Components::DebugComponent());

	//g.SetAmbientLight({ 1,1,1 });

	//HMEngine::Player p("Player");

	//g.AddGameObject(p);
	g.AddGameObject(gameMaster);

	//HMEngine::Core::Rendering::Camera::GetInstance().SetPosition(0.0f, 2.0f, 0.0f);

	int c = 0;
	/*for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			c++;
			HMEngine::Core::GameObject go(std::to_string(c));
			go.GetTransform().SetPosition(float(j * 2), float(i * 2) + 4, 0);
			if (c % 2 != 0)
				go.AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/bricks.png"));
			else
				go.AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/black.png"));
			g.AddGameObject(go);
		}
	}//
	//g.AddGameObject(go);
	//g.AddGameObject(go2);

	//g.SetAmbientLight({ 1,1,1 });
	//g.DisableFog();

	HMEngine::Player p("Player", 100.0f, 200.0f);
	//g.AddGameObject(p);

	HMEngine::UI::Image crosshair = HMEngine::UI::Image("crosshair", "./resources/UITextures/crosshair.png", { 400, 300 }, { 40, 30 });
	g.AddUI(crosshair);
	HMEngine::UI::Button button = HMEngine::UI::Button("button", "./resources/UITextures/UIButtonReleased.png", "./resources/UITextures/UIButtonHover.png", "./resources/UITextures/UIButtonPressed.png", { 400, 100 }, { 100, 30 });
	g.AddUI(button);

	//HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, "./resources/textures/grass.png", "./resources/textures/mud.png", "./resources/textures/veryNice.png", "./resources/textures/path.png", "./resources/textures/blendMap.png");
	//HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, "./resources/textures/grass.png");
	//HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, 40, "./resources/heightMaps/heightMap1.png", "./resources/textures/grass.png");
	HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, 40, "./resources/heightMaps/heightMap1.png", "./resources/textures/grass.png", "./resources/textures/mud.png", "./resources/textures/grassFlowers.png", "./resources/textures/path.png", "./resources/textures/blendMap.png");
	g.AddGameObject(terrain);

	g.UnlockCursor();
	g.SetMouseVisible(true);

	HMEngine::Core::Rendering::Camera::GetInstance().SetPosition(0.0f, 5.0f, -5.0f);
	g.Run();
	*/
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) //try to initialize SDL
	{
		HMEngine::Core::Utilities::ThrowException("SDL INITIALIZATION FAILED!");
	}
	HMEngine::Core::Utilities::PrintDebugMessage("Succeeded initializing SDL...");
	SDL_Window* window = SDL_CreateWindow("kaki", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	HMEngine::UI::Font arial = HMEngine::UI::Font("./resources/fonts/arial.fnt", "./resources/fonts/arial.png");
	HMEngine::UI::Font arial2 = HMEngine::UI::Font("./resources/fonts/arial.fnt", "./resources/fonts/arial.png");
	std::vector<glm::vec2> vertices = { glm::vec2(0,0), glm::vec2(1,0.5f) };
	std::vector<glm::vec3> uvs = { glm::vec3(0,1.5f, 5.2f), glm::vec3(1,5,69.21f) };
	std::vector<glm::vec4> kaki = { glm::vec4(1, 4, 5, 6) };
	//HMEngine::OpenGL::OpenGLQuad quad = HMEngine::OpenGL::OpenGLQuad(vertices);
	std::vector<std::any> hi = { 5, 1.2f, "a" };
	HMEngine::OpenGL::OpenGLObject object = HMEngine::OpenGL::OpenGLObject(hi);
	//HMEngine::OpenGL::OpenGLObject object = HMEngine::OpenGL::OpenGLObject(vertices, uvs, kaki);
	//HMEngine::OpenGL::OpenGLObject object2 = object;
	//HMEngine::OpenGL::OpenGLObject object3 = HMEngine::OpenGL::OpenGLObject(object);

	auto k = object.GetVBOData();
	for (auto& data : k)
	{
		if (data.type() == typeid(std::vector<glm::vec2>))
		{
			auto vec = std::any_cast<std::vector<glm::vec2>>(data);
			for (auto v : vec)
			{
				std::cout << v.x << ", " << v.y << std::endl;
			}
		}
		else if (data.type() == typeid(std::vector<glm::vec3>))
		{
			auto vec = std::any_cast<std::vector<glm::vec3>>(data);
			for (auto v : vec)
			{
				std::cout << v.x << ", " << v.y << ", " << v.z << std::endl;
			}
		}
		else if (data.type() == typeid(std::vector<glm::vec4>))
		{
			auto vec = std::any_cast<std::vector<glm::vec4>>(data);
			for (auto v : vec)
			{
				std::cout << v.x << ", " << v.y << ", " << v.z << ", " << v.w << std::endl;
			}
		}
	}

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	system("pause");
	return 0;
}