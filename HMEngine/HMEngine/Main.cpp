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
#include "Label.h"
#include <string>
#include "OpenGLObject.h"
#include "OpenGLQuad.h"
#include "TextBox.h"

int main()
{
	std::string title = "HMEngine";

	HMEngine::GameEngine g;
	g.CreateNewWindow(1200, 720, title, false);

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

	HMEngine::GameSettings::CalculateFPS(true);

	HMEngine::Core::GameObject gameMaster("master");
	//gameMaster.AddComponent(HMEngine::Components::DebugComponent());
	//g.AddGameObject(gameMaster);

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
	}*/
	//g.AddGameObject(go);
	//g.AddGameObject(go2);

	g.SetAmbientLight({ 1,1,1 });
	//g.DisableFog();

	HMEngine::Core::GameObject testObject("test");
	testObject.AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/VeryNice.png"));
	testObject.GetTransform().SetPositionY(10);
	g.AddGameObject(testObject);

	HMEngine::UI::Font arial = HMEngine::UI::Font("./resources/fonts/Arial.fnt", "./resources/fonts/Arial.png");

	HMEngine::UI::Image crosshair = HMEngine::UI::Image("crosshair", "./resources/UITextures/crosshair.png", { 600, 360 }, { 25, 25 });
	g.AddUI(crosshair);

	//HMEngine::UI::Button button = HMEngine::UI::Button("button", "./resources/UITextures/UIButtonReleased.png",
	//	"./resources/UITextures/UIButtonHover.png", "./resources/UITextures/UIButtonPressed.png", { 600, 650 }, { 90, 30 }, "Refresh", arial, { 0, 0, 0 }, 0.8f);
	//g.AddUI(button);

	HMEngine::UI::Label label = HMEngine::UI::Label("label", { 600, 360 }, "HI!", arial, { 0,0,0 }, 1.0f);
	g.AddUI(label);

	HMEngine::UI::TextBox txtBox = HMEngine::UI::TextBox("txtBox", { 600, 500 }, { 100, 30 }, arial);
	g.AddUI(txtBox);

	//HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, "./resources/textures/grass.png", "./resources/textures/mud.png", "./resources/textures/veryNice.png", "./resources/textures/path.png", "./resources/textures/blendMap.png");
	//HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, "./resources/textures/grass.png");
	//HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, 40, "./resources/heightMaps/heightMap1.png", "./resources/textures/grass.png");
	HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, 40, "./resources/heightMaps/heightMap1.png", "./resources/textures/grass.png", "./resources/textures/mud.png", "./resources/textures/grassFlowers.png", "./resources/textures/path.png", "./resources/textures/blendMap.png");
	g.AddGameObject(terrain);

	HMEngine::Player p("Player", 100.0f, 200.0f);
	//g.AddGameObject(p);

	g.UnlockCursor();
	g.SetMouseVisible(true);

	HMEngine::Core::Rendering::Camera::GetInstance().SetPosition(0.0f, 5.0f, -5.0f);
	g.Run();

	return 0;
}