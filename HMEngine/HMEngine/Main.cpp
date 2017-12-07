#include "HMEngineIncludes.h"

int main()
{
	std::string title = "test";

	HMEngine::GameEngine g;
	g.CreateNewWindow(800, 600, title, false);
	
	g.Run();

	//create cube
	 std::vector<glm::vec3> vertices =
	{
		(glm::vec3(0.5, -0.5, -0.5)), (glm::vec3(0.5, 0.5, -0.5)), (glm::vec3(-0.5, 0.5, -0.5)), (glm::vec3(-0.5, -0.5, -0.5)),
		(glm::vec3(0.5, -0.5, 0.5)), (glm::vec3(0.5, 0.5, 0.5)), (glm::vec3(-0.5, 0.5, 0.5)), (glm::vec3(-0.5, -0.5, 0.5)),
		(glm::vec3(0.5, -0.5, -0.5)), (glm::vec3(0.5, 0.5, -0.5)), (glm::vec3(0.5, 0.5, 0.5)), (glm::vec3(0.5, -0.5, 0.5)),
		(glm::vec3(-0.5, -0.5, 0.5)), (glm::vec3(-0.5, 0.5, 0.5)), (glm::vec3(-0.5, 0.5, -0.5)), (glm::vec3(-0.5, -0.5, -0.5)),
		(glm::vec3(0.5, 0.5, 0.5)), (glm::vec3(0.5, 0.5, -0.5)), (glm::vec3(-0.5, 0.5, -0.5)), (glm::vec3(-0.5, 0.5, 0.5)),
		(glm::vec3(0.5, -0.5, -0.5)), (glm::vec3(0.5, -0.5, 0.5)), (glm::vec3(-0.5, -0.5, 0.5)), (glm::vec3(-0.5, -0.5, -0.5))

	};
	HMEngine::Core::GameObject go;
	go.SetVertices(vertices);
	g.AddGameObject(go);




	return 0;
}