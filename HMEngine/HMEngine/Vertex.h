#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class Vertex
		{
		public:
			Vertex(const glm::vec3& pos) { this->_pos = pos; };
			~Vertex() {};
			
			Vertex GetPos() { return this->_pos; };
			float GetPosX() { return this->_pos.x; };
			float GetPosY() { return this->_pos.y; };
			float GetPosZ() { return this->_pos.z; };
			void SetPos(const glm::vec3 pos) { this->_pos = pos; };
			void SetPosX(const float posX) { this->_pos.x = posX; };
			void SetPosY(const float posY) { this->_pos.y = posY; };
			void SetPosZ(const float posZ) { this->_pos.z = posZ; };

			
		private:
			glm::vec3 _pos;

		};
	}
}