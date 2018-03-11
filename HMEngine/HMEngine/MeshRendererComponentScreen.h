#pragma once
#include "Screen.h"
#include "glm\glm.hpp"

namespace HMEngine
{
	namespace UI
	{
		class TextBox;
	}

	namespace Core
	{
		namespace WorldEditor
		{
			namespace ComponentScreens
			{
				class MeshRendererComponentScreen : public HMEngine::UI::Screen
				{
				public:
					MeshRendererComponentScreen(const glm::vec2& centerPos);
					~MeshRendererComponentScreen();

				private:
					HMEngine::UI::TextBox* _txtObjFilePath;
					HMEngine::UI::TextBox* _txtTextureFilePath;
				};
			}
		}
	}
}