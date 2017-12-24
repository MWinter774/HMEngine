#include "HMEngineIncludes.h"

int main()
{
	std::string title = "test";

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
	HMEngine::Core::GameObject go;
	go.SetVertices(vertices);

	g.AddGameObject(go);
	HMEngine::Core::Rendering::Shaders::BasicShader _shader;


	g.Run(_shader);




	return 0;
}