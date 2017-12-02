#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	class Transform
	{
	public:
		Transform(const glm::vec3& position = { 0,0,0 }, const glm::vec3& rotation = { 0,0,0 }, const glm::vec3& scale = { 1,1,1 });
		~Transform();

		/* Position getters/setters */
		inline float GetPositionX() const { return this->_position.x; }
		inline float GetPositionY() const { return this->_position.y; }
		inline float GetPositionZ() const { return this->_position.z; }
		inline glm::vec3 GetPosition()const { return this->_position; }
		inline void SetPositionX(float x) { this->_position.x = x; }
		inline void SetPositionY(float y) { this->_position.y = y; }
		inline void SetPositionZ(float z) { this->_position.z = z; }
		inline void SetPosition(const glm::vec3& other) { this->_position = other; }
		inline void SetPosition(float x, float y, float z) { this->_position = { x,y,z }; }

		/* Rotation getters/setters */
		inline float GetRotationX() const { return this->_rotation.x; }
		inline float GetRotationY() const { return this->_rotation.y; }
		inline float GetRotationZ() const { return this->_rotation.z; }
		inline glm::vec3 GetRotation() const { return this->_rotation; }
		inline void SetRotationX(float x) { this->_rotation.x = x; }
		inline void SetRotationY(float y) { this->_rotation.y = y; }
		inline void SetRotationZ(float z) { this->_rotation.z = z; }
		inline void SetRotation(const glm::vec3& other) { this->_rotation = other; }
		inline void SetRotation(float x, float y, float z) { this->_rotation = { x,y,z }; }

		/* Scale getters/setters */
		inline float GetScaleX() const { return this->_scale.x; }
		inline float GetScaleY() const { return this->_scale.y; }
		inline float GetScaleZ() const { return this->_scale.z; }
		inline glm::vec3 GetScale() const { return this->_scale; }
		inline void SetScaleX(float x) { this->_scale.x = x; }
		inline void SetScaleY(float y) { this->_scale.y = y; }
		inline void SetScaleZ(float z) { this->_scale.z = z; }
		inline void SetScale(const glm::vec3& other) { this->_scale = other; }
		inline void SetScale(float x, float y, float z) { this->_scale = { x,y,z }; }

		glm::mat4 GetModelMatrix() const;
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetMVPMatrix() const;

	private:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;
	};
}