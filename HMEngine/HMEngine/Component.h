#pragma once
#include "HMEngineIncludes.h"

namespace HMEngine
{
	namespace Core
	{
		class GameObject;
	}

	namespace Components
	{
		class Component
		{
			//friend class HMEngine::Core::GameObject;
		public:
			void SetParent(HMEngine::Core::GameObject& parent) { this->_parentObject = &parent; };
			HMEngine::Core::GameObject* GetParent() { return this->_parentObject; };

			virtual void Render() = 0;

			Component() {};
			virtual ~Component() {};

		protected:
			HMEngine::Core::GameObject* _parentObject = nullptr;
		};


		class Draw : public Component
		{
			//friend class HMEngine::Core::GameObject;
		public:
			void Render();
		};
	}
}