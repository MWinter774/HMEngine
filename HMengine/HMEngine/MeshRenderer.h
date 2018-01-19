#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Component.h"
#include "Mesh.h"


namespace HMEngine
{
	namespace OpenGL
	{
		class Texture;
	}

	namespace Components
	{

		class MeshRenderer : public Component
		{
		public:
			MeshRenderer(const std::string& meshPath, const std::string& texturePath, float shineDamper = 0.5f, float reflectivity = 1.0f);
			virtual ~MeshRenderer();
			MeshRenderer(const HMEngine::Components::MeshRenderer& other);
			HMEngine::Components::MeshRenderer& operator=(const HMEngine::Components::MeshRenderer& other);

			void DrawMesh();

			void AttachToGameObjectEvent() override;
			inline HMEngine::Components::MeshRenderer* Clone() override { return new HMEngine::Components::MeshRenderer(*this); }

			inline HMEngine::OpenGL::Texture& GetTexture() const { return *this->_texture; }
			inline float GetShineDamper() const { return this->_shineDamper; }
			inline float GetReflectivity() const { return this->_reflectivity; }

			void SetTexture(const std::string& texturePath);
			inline void SetShineDamper(float shineDamper) { this->_shineDamper = shineDamper; }
			inline void SetReflectivity(float reflectivity) { this->_reflectivity = reflectivity; }

		private:
			std::string _texturePath;
			std::string _meshPath;
			HMEngine::OpenGL::Texture* _texture;
			HMEngine::Core::Mesh* _mesh;

			bool _isAddedToRenderingEngine;
			float _shineDamper;
			float _reflectivity;
		};
	}
}