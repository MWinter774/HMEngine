#pragma once
//#include "HMEngineIncludes.h"
#include <glm\glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\matrix_transform_2d.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

namespace HMEngine
{
	namespace Core
	{
		class Transform
		{
		public:
			Transform(const glm::vec3& position = { 0,0,0 }, const glm::vec3& rotation = { 0,0,0 }, const glm::vec3& scale = { 1,1,1 });
			~Transform();

			//Transform operator=(const Transform& transform); 

			/* Position getters/setters/adders */
			inline float GetPositionX() const { return this->_position.x; }
			inline float GetPositionY() const { return this->_position.y; }
			inline float GetPositionZ() const { return this->_position.z; }
			inline glm::vec3 GetPosition()const { return this->_position; }
			inline void SetPositionX(float x) { this->_position.x = x; this->UpdateTranslationMatrix(); }
			inline void SetPositionY(float y) { this->_position.y = y; this->UpdateTranslationMatrix(); }
			inline void SetPositionZ(float z) { this->_position.z = z; this->UpdateTranslationMatrix(); }
			inline void SetPosition(const glm::vec3& other) { this->_position = other; this->UpdateTranslationMatrix(); }
			inline void SetPosition(float x, float y, float z) { this->_position = { x,y,z }; this->UpdateTranslationMatrix(); }
			inline void AddPositionX(float x) { this->_position.x += x; this->UpdateTranslationMatrix(); }
			inline void AddPositionY(float y) { this->_position.y += y; this->UpdateTranslationMatrix(); }
			inline void AddPositionZ(float z) { this->_position.z += z; this->UpdateTranslationMatrix(); }
			inline void AddPosition(const glm::vec3& other) { this->_position += other; this->UpdateTranslationMatrix(); }
			inline void AddPosition(float x, float y, float z) { this->_position += glm::vec3(x, y, z); this->UpdateTranslationMatrix(); }
			inline void AddPosition(float count) { this->_position += glm::vec3(count, count, count); this->UpdateTranslationMatrix(); }

			/* Rotation getters/setters/adders */
			inline float GetRotationX() const { return this->_rotation.x; }
			inline float GetRotationY() const { return this->_rotation.y; }
			inline float GetRotationZ() const { return this->_rotation.z; }
			inline glm::vec3 GetRotation() const { return this->_rotation; }
			inline void SetRotationX(float x) { this->_rotation.x = x; this->UpdateRotationMatrix(); }
			inline void SetRotationY(float y) { this->_rotation.y = y; this->UpdateRotationMatrix(); }
			inline void SetRotationZ(float z) { this->_rotation.z = z; this->UpdateRotationMatrix(); }
			inline void SetRotation(const glm::vec3& other) { this->_rotation = other; this->UpdateRotationMatrix(); }
			inline void SetRotation(float x, float y, float z) { this->_rotation = { x,y,z }; this->UpdateRotationMatrix(); }
			inline void AddRotationX(float x) { this->_rotation.x += x; this->UpdateRotationMatrix(); }
			inline void AddRotationY(float y) { this->_rotation.y += y; this->UpdateRotationMatrix(); }
			inline void AddRotationZ(float z) { this->_rotation.z += z; this->UpdateRotationMatrix(); }
			inline void AddRotation(const glm::vec3& other) { this->_rotation += other; this->UpdateRotationMatrix(); }
			inline void AddRotation(float x, float y, float z) { this->_rotation += glm::vec3(x, y, z); this->UpdateRotationMatrix(); }

			/* Scale getters/setters/adders */
			inline float GetScaleX() const { return this->_scale.x; }
			inline float GetScaleY() const { return this->_scale.y; }
			inline float GetScaleZ() const { return this->_scale.z; }
			inline glm::vec3 GetScale() const { return this->_scale; }
			inline void SetScaleX(float x) { this->_scale.x = x; this->UpdateScaleMatrix(); }
			inline void SetScaleY(float y) { this->_scale.y = y; this->UpdateScaleMatrix(); }
			inline void SetScaleZ(float z) { this->_scale.z = z; this->UpdateScaleMatrix(); }
			inline void SetScale(const glm::vec3& other) { this->_scale = other; this->UpdateScaleMatrix(); }
			inline void SetScale(float x, float y, float z) { this->_scale = { x,y,z }; this->UpdateScaleMatrix(); }
			inline void AddScaleX(float x) { this->_scale.x += x; this->UpdateScaleMatrix(); }
			inline void AddScaleY(float y) { this->_scale.y += y; this->UpdateScaleMatrix(); }
			inline void AddScaleZ(float z) { this->_scale.z += z; this->UpdateScaleMatrix(); }
			inline void AddScale(const glm::vec3& other) { this->_scale += other; this->UpdateScaleMatrix(); }
			inline void AddScale(float x, float y, float z) { this->_scale += glm::vec3(x, y, z); this->UpdateScaleMatrix(); }

			inline glm::quat GetRotationQuat() const { return this->_rotationQuat; }

			void LookAt(const glm::vec3& dst);

			glm::mat4 GetTranslationMatrix() const;
			glm::mat4 GetModelMatrix() const;
			glm::mat4 GetViewMatrix() const;
			glm::mat4 GetMVPMatrix() const;

		private:
			glm::vec3 _position;
			glm::vec3 _rotation;
			glm::quat _rotationQuat;
			glm::vec3 _scale;

			glm::mat4 _translationMatrix;
			glm::mat4 _rotationMatrix;
			glm::mat4 _scaleMatrix;
			glm::mat4 _transformationMatrix;

			void UpdateTranslationMatrix();
			void UpdateRotationMatrix();
			void UpdateScaleMatrix();
		};
	}
}