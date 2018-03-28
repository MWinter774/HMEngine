#include "Billboard.h"
#include "Label.h"

HMEngine::UI::Billboard::Billboard::Billboard(const std::string& name, const glm::vec3& positionInWorld, HMEngine::UI::Quad* quad) : 
	HMEngine::UI::Quad(name, positionInWorld, quad->GetScale()), _quad{ nullptr, nullptr }
{
	this->InitializeEvents<Billboard>(this);
	if (auto label = dynamic_cast<HMEngine::UI::Label*>(quad))
	{
		this->_quad.label = label;
	}
	else
	{
		this->_quad.quad = quad;
		this->_quad.quad->SetPosition(positionInWorld);
		for (auto& child : this->_quad.quad->GetChilds())
		{
			child->SetPosition(positionInWorld);
		}
	}
}

HMEngine::UI::Billboard::Billboard::~Billboard()
{
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().RemoveBillboard(*this);
	if (this->_quad.quad != nullptr)
	{
		delete this->_quad.quad;
	}
	else if (this->_quad.label != nullptr)
	{
		delete this->_quad.label;
	}
}

HMEngine::UI::Billboard::Billboard(const HMEngine::UI::Billboard& other) : HMEngine::UI::Quad(other)
{
	this->InitializeEvents<Billboard>(this);
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddBillboard(*this);
	if (other._quad.quad != nullptr)
	{
		this->_quad.quad = other._quad.quad->Clone();
	}
	else if (other._quad.label != nullptr)
	{
		this->_quad.label = static_cast<HMEngine::UI::Label*>(other._quad.label->Clone());
	}
}

HMEngine::UI::Billboard& HMEngine::UI::Billboard::operator=(const HMEngine::UI::Billboard& other)
{
	if (this != &other)
	{
		if (this->_quad.quad != nullptr)
		{
			delete this->_quad.quad;
		}
		else if (this->_quad.label != nullptr)
		{
			delete this->_quad.label;
		}

		this->InitializeEvents<Billboard>(this);
		if (other._quad.quad != nullptr)
		{
			this->_quad.quad = other._quad.quad->Clone();
		}
		else if (other._quad.label != nullptr)
		{
			this->_quad.label = static_cast<HMEngine::UI::Label*>(other._quad.label->Clone());
		}
	}

	return *this;
}

void HMEngine::UI::Billboard::AttachToGameEngineEvent()
{
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddBillboard(*this);
}
