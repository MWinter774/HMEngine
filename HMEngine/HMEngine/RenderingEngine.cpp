#include "RenderingEngine.h"

HMEngine::Core::Rendering::RenderingEngine& HMEngine::Core::Rendering::RenderingEngine::GetInstance()
{
	static HMEngine::Core::Rendering::RenderingEngine& instance = HMEngine::Core::Rendering::RenderingEngine();
	return instance;
}

void HMEngine::Core::Rendering::RenderingEngine::Render(const std::vector<HMEngine::Core::GameObject>& gameObjects) const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//HMEngine::Core::Rendering::Shaders::BasicShader::GetInstance().Bind();
	for (auto& gameObject : gameObjects)
	{
		//Draw gameObject
		gameObject.Draw();
	}
}

HMEngine::Core::Rendering::RenderingEngine::RenderingEngine()
{
}

HMEngine::Core::Rendering::RenderingEngine::~RenderingEngine()
{
}