#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class Transform
		{
		public:
			static void UpdateProjectionMatrix();

			Transform(const glm::vec3& position = { 0,0,10 }, const glm::vec3& rotation = { 0,0,0 }, const glm::vec3& scale = { 1,1,1 });
			~Transform();

			Transform operator=(const Transform& transform); 

			/* Position getters/setters/adders */
			inline float GetPositionX() const { return this->_position.x; }
			inline float GetPositionY() const { return this->_position.y; }
			inline float GetPositionZ() const { return this->_position.z; }
			inline glm::vec3 GetPosition()const { return this->_position; }
			inline void SetPositionX(float x) { this->_position.x = x; }
			inline void SetPositionY(float y) { this->_position.y = y; }
			inline void SetPositionZ(float z) { this->_position.z = z; }
			inline void SetPosition(const glm::vec3& other) { this->_position = other; }
			inline void SetPosition(float x, float y, float z) { this->_position = { x,y,z }; }
			inline void AddPositionX(float x) { this->_position.x += x; };
			inline void AddPositionY(float y) { this->_position.y += y; };
			inline void AddPositionZ(float z) { this->_position.z += z; };
			inline void AddPosition(const glm::vec3& other) { this->_position += other; };
			inline void AddPosition(float x, float y, float z) { this->_position += glm::vec3(x, y, z); };

			/* Rotation getters/setters/adders */
			inline float GetRotationX() const { return this->_rotation.x; }
			inline float GetRotationY() const { return this->_rotation.y; }
			inline float GetRotationZ() const { return this->_rotation.z; }
			inline glm::vec3 GetRotation() const { return this->_rotation; }
			inline void SetRotationX(float x) { this->_rotation.x = x; }
			inline void SetRotationY(float y) { this->_rotation.y = y; }
			inline void SetRotationZ(float z) { this->_rotation.z = z; }
			inline void SetRotation(const glm::vec3& other) { this->_rotation = other; }
			inline void SetRotation(float x, float y, float z) { this->_rotation = { x,y,z }; }
			inline void AddRotationX(float x) { this->_rotation.x += x; };
			inline void AddRotationY(float y) { this->_rotation.y += y; };
			inline void AddRotationZ(float z) { this->_rotation.z += z; };
			inline void AddRotation(const glm::vec3& other) { this->_rotation += other; };
			inline void AddRotation(float x, float y, float z) { this->_rotation += glm::vec3(x, y, z); };

			/* Scale getters/setters/adders */
			inline float GetScaleX() const { return this->_scale.x; }
			inline float GetScaleY() const { return this->_scale.y; }
			inline float GetScaleZ() const { return this->_scale.z; }
			inline glm::vec3 GetScale() const { return this->_scale; }
			inline void SetScaleX(float x) { this->_scale.x = x; }
			inline void SetScaleY(float y) { this->_scale.y = y; }
			inline void SetScaleZ(float z) { this->_scale.z = z; }
			inline void SetScale(const glm::vec3& other) { this->_scale = other; }
			inline void SetScale(float x, float y, float z) { this->_scale = { x,y,z }; }
			inline void AddScaleX(float x) { this->_scale.x += x; };
			inline void AddScaleY(float y) { this->_scale.y += y; };
			inline void AddScaleZ(float z) { this->_scale.z += z; };
			inline void AddScale(const glm::vec3& other) { this->_scale += other; };
			inline void AddScale(float x, float y, float z) { this->_scale += glm::vec3(x, y, z); };

			glm::mat4 GetModelMatrix() const;
			glm::mat4 GetViewMatrix() const;
			glm::mat4 GetProjectionMatrix() const;
			glm::mat4 GetMVPMatrix() const;

		private:
			static glm::mat4 projectionMatrix;

			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::vec3 _scale;
		};
	}
}