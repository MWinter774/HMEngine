#pragma once
#include "GameObject.h"
#include <string>
#include <glm\glm.hpp>

namespace HMEngine
{
	namespace Components
	{
		class TerrainRenderer;
	}
	class Terrain : public HMEngine::Core::GameObject
	{
	public:
		Terrain(const std::string& name, const glm::vec3& position, unsigned int size, const std::string& texturePath);
		~Terrain();
		Terrain(const HMEngine::Terrain& other);
		HMEngine::Terrain& operator=(const HMEngine::Terrain& other);

	private:
		HMEngine::Components::TerrainRenderer* _terrainRenderer;
	};
}