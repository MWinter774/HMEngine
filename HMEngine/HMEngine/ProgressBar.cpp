#include "ProgressBar.h"
#include "Image.h"

HMEngine::UI::ProgressBar::ProgressBar(const std::string& name, const glm::vec2& position, const glm::vec2& scale, const std::string& backgroundTexturePath,
	const std::string& barTexturePath, float percentage, bool is3D) : HMEngine::UI::Quad(name, position, scale), _percentage(percentage),
	_background(new HMEngine::UI::Image(name + "_backround", backgroundTexturePath, position, scale)),
	_bar(new HMEngine::UI::Image(name + "_bar", barTexturePath, position, scale)), _is3D(is3D)
{
	if (is3D)
	{
		this->_bar->SetPosition(glm::vec3(position, 0));
		this->_bar->SetScale(glm::vec3((scale.x - 0.08f) * (this->_percentage / 100.0f), scale.y - 0.1f, 0));

		this->_background->SetPosition(glm::vec3(position, 0));
		this->_background->SetScale(glm::vec3(scale, 0));
		this->_bar->SetTopLeft(this->_background->GetTopLeft3DSpace());
		this->AddChild(this->_bar);
		this->AddChild(this->_background);
	}
	else
	{
		this->_bar->SetPosition(position);
		this->_bar->SetScale((scale.x - scale.x / 100.0f) * (this->_percentage / 100.0f), scale.y - (scale.y / 15.0f));

		this->_background->SetPosition(position);
		this->_background->SetScale(scale);
		this->_bar->SetTopLeft(this->_background->GetTopLeft() + glm::vec2(scale.x / 200.0f, scale.y / 45.0f));
		this->AddChild(this->_background);
		this->AddChild(this->_bar);
	}
}

HMEngine::UI::ProgressBar::~ProgressBar()
{
}

void HMEngine::UI::ProgressBar::SetPercentage(float percentage)
{
	this->_percentage = percentage;
	if (this->_is3D)
	{
		this->_bar->SetScale(glm::vec3((this->GetScale().x - 0.08f) * (this->_percentage / 100.0f), this->GetScale().y - 0.1f, 0));
		this->_bar->SetTopLeft(this->_background->GetTopLeft3DSpace());
	}
	else
	{
		auto scaleX = this->GetScale().x;
		auto scaleY = this->GetScale().y;
		auto newScaleX = (scaleX - scaleX / 100.0f) * (this->_percentage / 100.0f);
		auto newScaleY = scaleY - (scaleY / 15.0f);
		this->_bar->SetScale(newScaleX, newScaleY);
		this->_bar->SetTopLeft(this->_background->GetTopLeft() + glm::vec2(newScaleX / 200.0f, newScaleY / 45.0f));
	}
}