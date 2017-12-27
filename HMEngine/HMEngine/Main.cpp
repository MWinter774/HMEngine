#include "HMEngineIncludes.h"

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

	HMEngine::Core::GameObject go;
	HMEngine::Components::MeshRenderer* t = new HMEngine::Components::MeshRenderer(vertices, indices);
	go.AddComponent(t);

	g.AddGameObject(go);

	HMEngine::Core::Rendering::Camera::GetInstance().SetPosition(0.5f, 0.5f, -5.0f);
	g.Run();

	return 0;
}