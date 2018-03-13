#pragma once
#include "Screen.h"
#include "glm\glm.hpp"
#include <string>
#include <vector>
#include <functional>
#include <map>

namespace HMEngine
{
	namespace UI
	{
		class TextBox;
		class Button;
		class Label;
	}
	namespace Components
	{
		class Component;
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
					std::function<void(HMEngine::Components::Component*)> _addComponentEvent;

					MeshRendererComponentScreen(const glm::vec2& centerPos);
					~MeshRendererComponentScreen();

					void ShowEvent() override;

				private:
					static std::vector<std::string> SplitString(const std::string& stringToSplit, char delimeter);

					HMEngine::UI::Label* _lblTitle;
					HMEngine::UI::TextBox* _txtObjFilePath;
					HMEngine::UI::Label* _lblObjFileError;
					HMEngine::UI::TextBox* _txtTextureFilePath;
					HMEngine::UI::Label* _lblTextureFileError;
					HMEngine::UI::Button* _btnChooseObjFile;
					HMEngine::UI::Button* _btnChooseTextureFile;
					HMEngine::UI::Button* _btnAddComponent;

					std::map<std::string, std::string> _filePaths; //maps between name of file(that exists in the text box) to the file path
				};
			}
		}
	}
}