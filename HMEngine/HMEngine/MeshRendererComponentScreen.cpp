#include "MeshRendererComponentScreen.h"
#include "TextBox.h"
#include "Fonts.h"
#include "Button.h"
#include <Windows.h>
#include <regex>
#include <sstream>
#include "Label.h"
#include "MeshRenderer.h"
#include "InvalidMeshFileException.h"
#include "InvalidTextureFileException.h"

std::string CreateChooseFileWindow(HMEngine::UI::Button* btn, const char* filter)
{
	HWND hwnd = CreateWindow("DYNAMIC", "dummy", WS_VISIBLE, int(btn->GetPosition().x), int(btn->GetPosition().y), 100, 100, NULL, NULL, NULL, NULL);
	OPENFILENAME ofn;
	char szFile[260] = { 0 };
	std::string filePath = "";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		filePath = ofn.lpstrFile;
	}

	DestroyWindow(hwnd);
	return filePath;
}

HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen::MeshRendererComponentScreen(const glm::vec2& centerPos) :
	HMEngine::UI::Screen("scrnMeshRenderer", centerPos, glm::vec2(400, 200)),
	_lblTitle(new HMEngine::UI::Label(this->_name + "_lblTitle", glm::vec2(centerPos.x, centerPos.y - 80), "MeshRenderer", HMEngine::Fonts::ARIAL, glm::vec3(), 1.0f)),
	_txtObjFilePath(new HMEngine::UI::TextBox(this->_name + "_txtObjFilePath", glm::vec2(centerPos.x - 20, centerPos.y - 40), glm::vec2(320, 25), HMEngine::Fonts::ARIAL)),
	_lblObjFileError(new HMEngine::UI::Label(this->_name + "_lblObjectFileError", glm::vec2(centerPos.x, centerPos.y - 15),
		"INVALID OBJECT FILE!", HMEngine::Fonts::ARIAL, glm::vec3(255, 0, 0), 1.0f)),
	_txtTextureFilePath(new HMEngine::UI::TextBox(this->_name + "_txtTextureFilePath", glm::vec2(centerPos.x - 20, centerPos.y + 12), glm::vec2(320, 25),
		HMEngine::Fonts::ARIAL)),
	_lblTextureFileError(new HMEngine::UI::Label(this->_name + "_lblTextureFileError", glm::vec2(centerPos.x, centerPos.y + 40),
		"INVLID TEXTURE!", HMEngine::Fonts::ARIAL, glm::vec3(255, 0, 0), 1.0f)),
	_btnChooseObjFile(new HMEngine::UI::Button(this->_name + "_btnChooseObjFile", "./resources/UITextures/UIButtonReleased.png",
		"./resources/UITextures/UIButtonHover.png", "./resources/UITextures/UIButtonPressed.png", glm::vec2(centerPos.x + 167, centerPos.y - 40), glm::vec2(40, 25),
		"...", HMEngine::Fonts::ARIAL, glm::vec3())),
	_btnChooseTextureFile(new HMEngine::UI::Button(this->_name + "_btnChooseTextureFile", "./resources/UITextures/UIButtonReleased.png",
		"./resources/UITextures/UIButtonHover.png", "./resources/UITextures/UIButtonPressed.png", glm::vec2(centerPos.x + 167, centerPos.y + 12), glm::vec2(40, 25),
		"...", HMEngine::Fonts::ARIAL, glm::vec3())),
	_btnAddComponent(new HMEngine::UI::Button(this->_name + "_btnAddComponent", "./resources/UITextures/NiceButtonReleased.png",
		"./resources/UITextures/NiceButtonHover.png", "./resources/UITextures/NiceButtonPressed.png", glm::vec2(centerPos.x, centerPos.y + 65),
		glm::vec2(120, 40), "Add Component", HMEngine::Fonts::ARIAL, glm::vec3()))
{
	*this->_btnChooseObjFile += [this](HMEngine::UI::Button* btn)
	{
		std::string filePath = CreateChooseFileWindow(btn, "Object File\0*.obj\0\0");
		std::string fileName = "";
		if (filePath.size() > 0)
		{
			fileName = HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen::SplitString(filePath, '\\').back();
			this->_filePaths[fileName] = filePath;
		}
		this->_txtObjFilePath->SetText(fileName);
	};
	*this->_btnChooseTextureFile += [this](HMEngine::UI::Button* btn)
	{
		std::string filePath = CreateChooseFileWindow(btn, "PNG File\0*.png\0\0");
		std::string fileName = "";
		if (filePath.size() > 0)
		{
			fileName = HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen::SplitString(filePath, '\\').back();
			this->_filePaths[fileName] = filePath;
		}
		this->_txtTextureFilePath->SetText(fileName);
	};
	*this->_btnAddComponent += [&](HMEngine::UI::Button* btn)
	{
		bool isValid = true;
		if (this->_txtObjFilePath->IsEmpty())
		{
			this->_lblObjFileError->Show();
			isValid = false;
		}
		else
		{
			this->_lblObjFileError->Hide();
		}
		if (this->_txtTextureFilePath->IsEmpty())
		{
			this->_lblTextureFileError->Show();
			isValid = false;
		}
		else
		{
			this->_lblTextureFileError->Hide();
		}
		if (isValid)
		{
			HMEngine::Components::MeshRenderer* meshRenderer = nullptr;
			try
			{
				meshRenderer = new HMEngine::Components::MeshRenderer(this->_filePaths[this->_txtObjFilePath->GetText()],
					this->_filePaths[this->_txtTextureFilePath->GetText()]);
			}
			catch (const HMEngine::Exceptions::InvalidMeshFileException&)
			{
				this->_lblObjFileError->Show();
			}
			catch (const HMEngine::Exceptions::InvalidTextureFileException&)
			{
				this->_lblTextureFileError->Show();
			}
			if (meshRenderer != nullptr)
				this->_addComponentEvent(meshRenderer);
		}
	};

	this->SetBackground("./resources/UITextures/AddGameObjectMenu.png");
	this->AddQuad(this->_lblTitle);
	this->AddQuad(this->_txtObjFilePath);
	this->AddQuad(this->_txtTextureFilePath);
	this->AddQuad(this->_btnChooseObjFile);
	this->AddQuad(this->_btnChooseTextureFile);
	this->AddQuad(this->_btnAddComponent);
	this->AddQuad(this->_lblObjFileError);
	this->AddQuad(this->_lblTextureFileError);

	this->Hide();
}

HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen::~MeshRendererComponentScreen()
{
}

void HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen::ShowEvent()
{
	this->_lblObjFileError->Hide();
	this->_lblTextureFileError->Hide();
}

std::vector<std::string> HMEngine::Core::WorldEditor::ComponentScreens::MeshRendererComponentScreen::SplitString(const std::string& stringToSplit, char delimeter)
{
	std::stringstream ss(stringToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (std::getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}
