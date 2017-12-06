#include "HMEngineIncludes.h"

int main()
{
	std::string title = "test";

	HMEngine::GameEngine g;
	g.CreateNewWindow(800, 600, title, false);
	
	g.Run();

	//create cube
	HMEngine::Core::Vertex vertices[] =
	{
		HMEngine::Core::Vertex(glm::vec3(0.5, -0.5, -0.5)), HMEngine::Core::Vertex(glm::vec3(0.5, 0.5, -0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, 0.5, -0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, -0.5, -0.5)),
		HMEngine::Core::Vertex(glm::vec3(0.5, -0.5, 0.5)), HMEngine::Core::Vertex(glm::vec3(0.5, 0.5, 0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, 0.5, 0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, -0.5, 0.5)),
		HMEngine::Core::Vertex(glm::vec3(0.5, -0.5, -0.5)), HMEngine::Core::Vertex(glm::vec3(0.5, 0.5, -0.5)), HMEngine::Core::Vertex(glm::vec3(0.5, 0.5, 0.5)), HMEngine::Core::Vertex(glm::vec3(0.5, -0.5, 0.5)),
		HMEngine::Core::Vertex(glm::vec3(-0.5, -0.5, 0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, 0.5, 0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, 0.5, -0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, -0.5, -0.5)),
		HMEngine::Core::Vertex(glm::vec3(0.5, 0.5, 0.5)), HMEngine::Core::Vertex(glm::vec3(0.5, 0.5, -0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, 0.5, -0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, 0.5, 0.5)),
		HMEngine::Core::Vertex(glm::vec3(0.5, -0.5, -0.5)), HMEngine::Core::Vertex(glm::vec3(0.5, -0.5, 0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, -0.5, 0.5)), HMEngine::Core::Vertex(glm::vec3(-0.5, -0.5, -0.5))

	};
	HMEngine::Core::GameObject go(vertices);
	g.AddGameObject(go);

	return 0;
}