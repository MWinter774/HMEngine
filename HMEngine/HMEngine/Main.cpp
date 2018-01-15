#include "HMEngineIncludes.h"
#include "GameObject.h"
#include "GameEngine.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "Player.h"
#include "Transform.h"
#include "Utilities.h"
#include "DebugComponent.h"
#include "Terrain.h"

int main()
{
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
	HMEngine::GameSettings::CalculateFPS(true);

	HMEngine::Core::GameObject go("d");
	HMEngine::Components::DebugComponent dc;
	go.AddComponent(dc);

	HMEngine::Core::GameObject go2("d");
	HMEngine::Components::MeshRenderer t2 = HMEngine::Components::MeshRenderer(vertices, indices, uvs, "./resources/textures/black.png");
	go2.GetTransform().SetPosition(2, 2, 0);
	go2.AddComponent(t2);


	int c = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			c++;
			HMEngine::Core::GameObject go(std::to_string(c));
			go.GetTransform().SetPosition(float(j * 2), float(i * 2) + 4, 0);
			if (c % 2 != 0)
				go.AddComponent(HMEngine::Components::MeshRenderer(vertices, indices, uvs, "./resources/textures/bricks.png"));
			else
				go.AddComponent(HMEngine::Components::MeshRenderer(vertices, indices, uvs, "./resources/textures/black.png"));
			g.AddGameObject(go);
		}
	}
	g.AddGameObject(go);
	//g.AddGameObject(go2);

	g.SetAmbientLight({ 1,1,1 });
	//g.DisableFog();

	HMEngine::Player p("Player", 100.0f, 200.0f);
	g.AddGameObject(p);

	HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, "./resources/textures/grass.png");
	g.AddGameObject(terrain);

	//g.UnlockCursor();
	//g.SetMouseVisible(true);

	HMEngine::Core::Rendering::Camera::GetInstance().SetPosition(0.0f, 5.0f, -5.0f);
	g.Run();

	return 0;
}