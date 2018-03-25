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
#include "BrainComponent.h"
#include "BoundingSphere.h"
#include "BoundingPlane.h"
#include "PhysicalPlayer.h"
#include "Billboard.h"
#include "Fonts.h"

int main()
{
	std::string title = "HMEngine";

	HMEngine::GameEngine g;
	g.CreateNewWindow(1200, 720, title, false);

	//HMEngine::Core::Rendering::Camera::GetInstance().SetPosition(0.0f, 2.0f, 0.0f);

	//int c = 0;
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

	//g.SetAmbientLight({ 1,1,1 });
	//g.DisableFog();

	//HMEngine::Core::GameObject testObject("test");
	//testObject.AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/cube.obj", "./resources/textures/VeryNice.png"));
	//testObject.GetTransform().SetPositionY(0);
	//g.AddGameObject(testObject);

	/*HMEngine::GameSettings::CalculateFPS(true);

	HMEngine::Core::GameObject gameMaster("master");
	gameMaster.AddComponent(HMEngine::Components::DebugComponent());
	g.AddGameObject(gameMaster);

	HMEngine::UI::Font arial = HMEngine::UI::Font("./resources/fonts/Arial.fnt", "./resources/fonts/Arial.png");

	HMEngine::UI::Image crosshair = HMEngine::UI::Image("crosshair", "./resources/UITextures/crosshair.png", { 600, 360 }, { 25, 25 });
	g.AddUI(crosshair);

	HMEngine::UI::Button button = HMEngine::UI::Button("button", "./resources/UITextures/UIButtonReleased.png",
		"./resources/UITextures/UIButtonHover.png", "./resources/UITextures/UIButtonPressed.png", { 600, 650 }, { 90, 30 }, "Refresh", arial, { 0, 0, 0 }, 0.8f);
	g.AddUI(button);

	HMEngine::UI::Label label = HMEngine::UI::Label("label", { 600, 360 }, "HI!", arial, { 0,0,0 }, 1.0f);
	g.AddUI(label);

	HMEngine::UI::TextBox txtBox = HMEngine::UI::TextBox("txtBox", { 600, 500 }, { 100, 30 }, arial);
	g.AddUI(txtBox);

	HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, 40, "./resources/heightMaps/heightMap1.png", "./resources/textures/grass.png", "./resources/textures/mud.png", "./resources/textures/grassFlowers.png", "./resources/textures/path.png", "./resources/textures/blendMap.png");
	g.AddGameObject(terrain);

	HMEngine::Player p("Player", 100.0f, 200.0f);
	g.AddGameObject(p);*/

	//HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, "./resources/textures/grass.png", "./resources/textures/mud.png", "./resources/textures/veryNice.png", "./resources/textures/path.png", "./resources/textures/blendMap.png");
	//HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, "./resources/textures/grass.png");
	//HMEngine::Terrain terrain("Terrain", glm::vec3(-100, 0, -100), 800, 40, "./resources/heightMaps/heightMap1.png", "./resources/textures/grass.png");

	//g.UnlockCursor();
	//g.SetMouseVisible(true);

	//g.InitializeWorldEditor(1200, 720, title, false);

	HMEngine::PhysicalPlayer* p = new HMEngine::PhysicalPlayer("player", 15, 30.0f);
	g.AddGameObject(p);

	//ML
	HMEngine::Core::GameObject floor("floor");
	floor.GetTransform().SetScaleX(10.0f);
	floor.GetTransform().SetScaleZ(10.0f);
	floor.AddComponent(HMEngine::Core::Physics::Colliders::BoundingPlane(0));
	HMEngine::Core::GameObject bot("bot");
	bot.GetTransform().AddPositionY(100.0f);
	bot.GetTransform().SetScaleZ(1.5f);
	bot.GetTransform().SetRotationX(1.57f);
	bot.AddComponent(HMEngine::Core::Physics::Colliders::BoundingSphere(10.0f));

	floor.AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/plane.obj", "./resources/textures/VeryNice.png"));

	bot.AddComponent(HMEngine::Components::MeshRenderer("./resources/objects/capsule.obj", "./resources/textures/mud.png"));
	bot.AddComponent(HMEngine::Components::BrainComponent(*p));

	HMEngine::UI::Image crosshair = HMEngine::UI::Image("crosshair", "./resources/UITextures/crosshair.png", { 600, 360 }, { 25, 25 });
	g.AddUI(crosshair);

	g.AddGameObject(floor);
	g.AddGameObject(bot);

	g.SetAmbientLight(1, 1, 1);

	HMEngine::UI::Image* ej = new HMEngine::UI::Image("imgEj", "./resources/UITextures/ej.png", { 600, 360 }, { 25 ,25});
	//HMEngine::UI::Label* lbl = new HMEngine::UI::Label("lblD", HMEngine::GameSettings::GetScreenCenter(), "DDD!", HMEngine::Fonts::ARIAL, glm::vec3(), 0.8f);
	HMEngine::UI::Billboard a("bKaki", { -20.0f,0,0 }, { 5,5 }, ej);
	g.AddUI(a);

	HMEngine::Core::Rendering::Camera::GetInstance().SetPosition(0.0f, 5.0f, -5.0f);
	g.Run();

	return 0;
}