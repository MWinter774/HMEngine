#include "RenderingEngine.h"
#include "MeshRenderer.h"
#include "Texture.h"
#include "OpenGLTexture.h"
#include "BasicShader.h"
#include "TerrainShader.h"
#include "GameObject.h"
#include "DirectionalLight.h"
#include "DirectionalLightShader.h"
#include "PointLight.h"
#include "PointLightShader.h"
#include "AmbientLightShader.h"
#include "GameSettings.h"
#include "TerrainRenderer.h"
#include <algorithm>
#include "Quad.h"
#include "UIShader.h"
#include "Label.h"
#include "LabelShader.h"

HMEngine::Core::Rendering::RenderingEngine& HMEngine::Core::Rendering::RenderingEngine::GetInstance()
{
	static HMEngine::Core::Rendering::RenderingEngine& instance = HMEngine::Core::Rendering::RenderingEngine();
	return instance;
}

void HMEngine::Core::Rendering::RenderingEngine::Render()
{
	this->CullFrustrum(); //Calculates which objects are visible

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(this->_skyColor.r, this->_skyColor.g, this->_skyColor.b, 1.0f);

	if (this->_meshTextures.size() > 0)
	{
		this->RenderMeshes();
	}
	if (this->_terrainRenderers.size() > 0)
	{
		this->RenderTerrains();
	}


	glEnable(GL_BLEND);
	if (this->_doCleanupForMeshes = (this->_directionalLights.size() > 0 || this->_pointLights.size() > 0))
	{
		glBlendFunc(GL_ONE, GL_ONE);
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_EQUAL);
	}

	if (this->_directionalLights.size() > 0) //if there are any directional lights then render all the meshed with the directional lights effect on them
	{
		HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().Bind();
		for (auto& item : this->_meshTextures)
		{
			item.first->Bind();
			for (auto& mesh : item.second)
			{
				for (auto& directionalLight : _directionalLights)
				{
					HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(*directionalLight);
					HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
					HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(mesh->GetShineDamper(), mesh->GetReflectivity());
					mesh->DrawMesh();
				}
			}
		}
		for (auto& terrain : this->_terrainRenderers)
		{
			for (auto& directionalLight : _directionalLights)
			{
				HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(*directionalLight);
				HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(terrain->GetParent().GetTransform());
				HMEngine::Core::Rendering::Shaders::DirectionalLightShader::GetInstance().UpdateUniforms(0.05f, 1.0f);
				terrain->BindTextures(); //Binds terrain textures
				terrain->DrawTerrain();
			}
		}
	}
	if (this->_pointLights.size() > 0) //if there are any point lights then render all the meshed with the point light effect on them
	{
		HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().Bind();
		for (auto& item : this->_meshTextures)
		{
			item.first->Bind();
			for (auto& mesh : item.second)
			{
				for (auto& pointLight : this->_pointLights)
				{
					HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(*pointLight);
					HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
					HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(mesh->GetShineDamper(), mesh->GetReflectivity());
					mesh->DrawMesh();
				}
			}
		}
		for (auto& terrain : this->_terrainRenderers)
		{
			for (auto& pointLight : this->_pointLights)
			{
				HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(*pointLight);
				HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(terrain->GetParent().GetTransform());
				HMEngine::Core::Rendering::Shaders::PointLightShader::GetInstance().UpdateUniforms(0.05f, 1.0f);
				terrain->BindTextures(); //Binds terrain textures
				terrain->DrawTerrain();
			}
		}
	}

	if (this->_doCleanupForQuads = this->_quads.size() > 0 || this->_labels.size() > 0)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
	}
	if (this->_quads.size() > 0)
	{
		this->RenderQuads();
	}
	if (this->_labels.size() > 0)
	{
		this->RenderLabels();
	}
	if (this->_doCleanupForQuads)
	{
		glEnable(GL_DEPTH_TEST);
	}

	if (this->_doCleanupForMeshes) //if there are some lights in the scene then load back the settings from blending the new lights
	{
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
	}
	glDisable(GL_BLEND);



	this->_meshTextures.clear(); //resets the objects that are visible
}

void HMEngine::Core::Rendering::RenderingEngine::AddMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer)
{
	this->_meshesToRender.push_back(&meshRenderer);
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveMeshRenderer(HMEngine::Components::MeshRenderer& meshRenderer)
{
	this->_meshesToRender.remove(&meshRenderer);
}

void HMEngine::Core::Rendering::RenderingEngine::AddTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer)
{
	this->_terrainRenderers.push_back(&terrainRenderer);
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveTerrainRenderer(HMEngine::Components::TerrainRenderer& terrainRenderer)
{
	this->_terrainRenderers.erase(std::remove(this->_terrainRenderers.begin(), this->_terrainRenderers.end(), &terrainRenderer), this->_terrainRenderers.end());
}

HMEngine::Core::Rendering::RenderingEngine::RenderingEngine() : _meshTextures(), _skyColor(HMEngine::GameSettings::GetSkyColor()), _terrainRenderers(), _directionalLights(), _pointLights(), _doCleanupForMeshes(false), _doCleanupForQuads(false)
{
	//glCullFace(GL_BACK); //Causes the back of things not to be drawn
	//glEnable(GL_CULL_FACE); //Causes the back of things not to be drawn
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
}

HMEngine::Core::Rendering::RenderingEngine::~RenderingEngine()
{
}

void HMEngine::Core::Rendering::RenderingEngine::RenderMeshes() const
{
	/* Renders meshes */
	bool hadTransparency = false;
	HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().Bind();
	for (auto& item : this->_meshTextures)
	{
		item.first->Bind();
		/* If the mesh has transparent texture then dont cull face */
		if (item.first->HasTransparency())
		{
			glDisable(GL_CULL_FACE);
			hadTransparency = true;
		}

		for (auto& mesh : item.second)
		{
			HMEngine::Core::Rendering::Shaders::AmbientLightShader::GetInstance().UpdateUniforms(mesh->GetParent().GetTransform());
			mesh->DrawMesh();
		}

		/* If the mesh had transparent texture then turn on cull */
		if (hadTransparency)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			hadTransparency = false;
		}
	}
}

void HMEngine::Core::Rendering::RenderingEngine::RenderTerrains() const
{
	/* Renders terrains */
	HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().Bind();
	for (auto& terrain : this->_terrainRenderers)
	{
		HMEngine::Core::Rendering::Shaders::TerrainShader::GetInstance().UpdateUniforms(terrain->GetParent().GetTransform());
		terrain->DrawTerrain();
	}
}

void HMEngine::Core::Rendering::RenderingEngine::RenderQuads() const
{
	HMEngine::Core::Rendering::Shaders::UIShader::GetInstance().Bind();
	for (auto& quad : this->_quads)
	{
		HMEngine::Core::Rendering::Shaders::UIShader::GetInstance().UpdateUniforms(quad->GetTransform());
		quad->Draw();
		for (auto& child : quad->GetChilds())
		{
			HMEngine::Core::Rendering::Shaders::UIShader::GetInstance().UpdateUniforms(child->GetTransform());
			child->Draw();
		}
	}
}

void HMEngine::Core::Rendering::RenderingEngine::RenderLabels() const
{
	HMEngine::Core::Rendering::Shaders::LabelShader::GetInstance().Bind();
	for (auto& label : this->_labels)
	{
		HMEngine::Core::Rendering::Shaders::LabelShader::GetInstance().UpdateUniforms(*label);
		label->Draw();
	}
}

/*
Calculates which objects are visible and updates the _meshTextures map accrodingly.
*/
void HMEngine::Core::Rendering::RenderingEngine::CullFrustrum()
{
	HMEngine::Core::Transform* objectTransform = nullptr;
	for (auto& meshRenderer : this->_meshesToRender)
	{
		objectTransform = &meshRenderer->GetParent().GetTransform();
		if (this->IsObjectVisible(objectTransform->GetMVPMatrix(), meshRenderer->GetCenter(), meshRenderer->GetRadius()))
		{
			this->_meshTextures[&meshRenderer->GetTexture().GetOpenGLTexture()].push_back(meshRenderer);
		}
	}
}

/*
Returns whether the object is visible or not.
Input:
objectMVPMatrix - mvp matrix of the object to check
objectPos - position of the object to check
radius - radius of the object capsule
Output:
True if object is seen, false of isn't.
*/
bool HMEngine::Core::Rendering::RenderingEngine::IsObjectVisible(const glm::mat4& objectMVPMatrix, const glm::vec3& objectPos, float radius)
{
	GLfloat xPos = objectPos.x, yPos = objectPos.y, zPos = objectPos.z;
	const GLfloat* MVPMatrix = glm::value_ptr(objectMVPMatrix);
	GLfloat leftPlane[4];
	GLfloat rightPlane[4];
	GLfloat bottomPlane[4];
	GLfloat nearPlane[4];
	GLfloat topPlane[4];
	GLfloat farPlane[4];
	GLfloat length;
	GLfloat distance;

	leftPlane[A] = MVPMatrix[3] + MVPMatrix[0];
	leftPlane[B] = MVPMatrix[7] + MVPMatrix[4];
	leftPlane[C] = MVPMatrix[11] + MVPMatrix[8];
	leftPlane[D] = MVPMatrix[15] + MVPMatrix[12];

	/* Normalise the plane */
	length = sqrtf(leftPlane[A] * leftPlane[A] + leftPlane[B] * leftPlane[B] + leftPlane[C] * leftPlane[C]);
	leftPlane[A] /= length;
	leftPlane[B] /= length;
	leftPlane[C] /= length;
	leftPlane[D] /= length;

	/* Check the point's location with respect to the left plane of viewing frustrum */
	distance = leftPlane[A] * xPos + leftPlane[B] * yPos + leftPlane[C] * zPos + leftPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the left plane

	/* Check the point's location with respect to the right plane of viewing frustum */
	rightPlane[A] = MVPMatrix[3] - MVPMatrix[0];
	rightPlane[B] = MVPMatrix[7] - MVPMatrix[4];
	rightPlane[C] = MVPMatrix[11] - MVPMatrix[8];
	rightPlane[D] = MVPMatrix[15] - MVPMatrix[12];

	/* Normalise the plane */
	length = sqrtf(rightPlane[A] * rightPlane[A] + rightPlane[B] * rightPlane[B] + rightPlane[C] * rightPlane[C]);
	rightPlane[A] /= length;
	rightPlane[B] /= length;
	rightPlane[C] /= length;
	rightPlane[D] /= length;

	distance = rightPlane[A] * xPos + rightPlane[B] * yPos + rightPlane[C] * zPos + rightPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the right plane

	/* Check the point's location with respect to the bottom plane of viewing frustum */
	bottomPlane[A] = MVPMatrix[3] + MVPMatrix[1];
	bottomPlane[B] = MVPMatrix[7] + MVPMatrix[5];
	bottomPlane[C] = MVPMatrix[11] + MVPMatrix[9];
	bottomPlane[D] = MVPMatrix[15] + MVPMatrix[13];

	/* Normalise the plane */
	length = sqrtf(bottomPlane[A] * bottomPlane[A] + bottomPlane[B] * bottomPlane[B] + bottomPlane[C] * bottomPlane[C]);
	bottomPlane[A] /= length;
	bottomPlane[B] /= length;
	bottomPlane[C] /= length;
	bottomPlane[D] /= length;

	distance = bottomPlane[A] * xPos + bottomPlane[B] * yPos + bottomPlane[C] * zPos + bottomPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the bottom plane

	/* Check the point's location with respect to the top plane of viewing frustrum */
	topPlane[A] = MVPMatrix[3] - MVPMatrix[1];
	topPlane[B] = MVPMatrix[7] - MVPMatrix[5];
	topPlane[C] = MVPMatrix[11] - MVPMatrix[9];
	topPlane[D] = MVPMatrix[15] - MVPMatrix[13];

	/* Normalise the plane */
	length = sqrtf(topPlane[A] * topPlane[A] + topPlane[B] * topPlane[B] + topPlane[C] * topPlane[C]);
	topPlane[A] /= length;
	topPlane[B] /= length;
	topPlane[C] /= length;
	topPlane[D] /= length;

	distance = topPlane[A] * xPos + topPlane[B] * yPos + topPlane[C] * zPos + topPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the top plane

	/* Check the point's location with respect to the near plane of viewing frustum */
	nearPlane[A] = MVPMatrix[3] + MVPMatrix[2];
	nearPlane[B] = MVPMatrix[7] + MVPMatrix[6];
	nearPlane[C] = MVPMatrix[11] + MVPMatrix[10];
	nearPlane[D] = MVPMatrix[15] + MVPMatrix[14];

	/* Normalise the plane */
	length = sqrtf(nearPlane[A] * nearPlane[A] + nearPlane[B] * nearPlane[B] + nearPlane[C] * nearPlane[C]);
	nearPlane[A] /= length;
	nearPlane[B] /= length;
	nearPlane[C] /= length;
	nearPlane[D] /= length;

	distance = nearPlane[A] * xPos + nearPlane[B] * yPos + nearPlane[C] * zPos + nearPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is completely outside the near plane

	/* Check the point's location with respect to the far plane of viewing frustum */
	farPlane[A] = MVPMatrix[3] - MVPMatrix[2];
	farPlane[B] = MVPMatrix[7] - MVPMatrix[6];
	farPlane[C] = MVPMatrix[11] - MVPMatrix[10];
	farPlane[D] = MVPMatrix[15] - MVPMatrix[14];

	/* Normalise the plane */
	length = sqrtf(farPlane[A] * farPlane[A] + farPlane[B] * farPlane[B] + farPlane[C] * farPlane[C]);
	farPlane[A] /= length;
	farPlane[B] /= length;
	farPlane[C] /= length;
	farPlane[D] /= length;

	distance = farPlane[A] * xPos + farPlane[B] * yPos + farPlane[C] * zPos + farPlane[D];
	if (distance <= -radius)
		return false; //Bounding sphere is outside the far plane

	/* The bounding sphere is within at least all six sides of the view frustum, so it's visible */
	return true;
}

void HMEngine::Core::Rendering::RenderingEngine::AddDirectionalLight(HMEngine::Components::DirectionalLight& directionalLight)
{
	_directionalLights.insert(&directionalLight);
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveDirectionalLight(HMEngine::Components::DirectionalLight& directionalLight)
{
	this->_directionalLights.erase(&directionalLight);
}

void HMEngine::Core::Rendering::RenderingEngine::AddPointLight(HMEngine::Components::PointLight& pointLight)
{
	this->_pointLights.insert(&pointLight);
}

void HMEngine::Core::Rendering::RenderingEngine::RemovePointLight(HMEngine::Components::PointLight& pointLight)
{
	this->_pointLights.erase(&pointLight);
}

void HMEngine::Core::Rendering::RenderingEngine::AddUI(HMEngine::UI::Quad& ui)
{
	if (typeid(ui) != typeid(HMEngine::UI::Label))
	{
		this->_quads.push_back(&ui);
	}
	else
		this->_labels.insert(static_cast<HMEngine::UI::Label*>(&ui));
}

void HMEngine::Core::Rendering::RenderingEngine::RemoveUI(HMEngine::UI::Quad& ui)
{
	//this->_quads.erase(&ui);
}