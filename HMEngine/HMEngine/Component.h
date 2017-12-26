#pragma once
//#include "HMEngineIncludes.h"

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
			friend class HMEngine::Core::GameObject;
		public:
			Component();
			virtual ~Component();

			inline HMEngine::Core::GameObject& GetParent() { return *this->_parentObject; };

			virtual void Render() {}

		protected:
			HMEngine::Core::GameObject* _parentObject;
		};


		class Draw : public Component
		{
		public:
			void Render() override;
		};
	}
}