#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Component.h"
#include "Mesh.h"


namespace HMEngine
{
	namespace Components
	{
		class Texture;

		class MeshRenderer : public Component
		{
		public:
			MeshRenderer(const std::string& meshPath, const std::string& texturePath);
			virtual ~MeshRenderer();
			MeshRenderer(const HMEngine::Components::MeshRenderer& other);
			HMEngine::Components::MeshRenderer& operator=(const HMEngine::Components::MeshRenderer& other);

			void DrawMesh();

			void AttachToGameObjectEvent() override;
			inline HMEngine::Components::MeshRenderer* Clone() override { return new HMEngine::Components::MeshRenderer(*this); }

			inline HMEngine::Components::Texture& GetTexture() const { return *this->_texture; }

		private:
			std::string _texturePath;
			std::string _meshPath;
			HMEngine::Components::Texture* _texture;
			HMEngine::Core::Mesh* _mesh;

			bool _isAddedToRenderingEngine;
		};
	}
}