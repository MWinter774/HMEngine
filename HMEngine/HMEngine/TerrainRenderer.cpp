#include "TerrainRenderer.h"
#include "Texture.h"
#include "TerrainTexture.h"
#include "RenderingEngine.h"
#include "Utilities.h"
#include "Mesh.h"

HMEngine::Components::TerrainRenderer::TerrainRenderer(unsigned int size, const std::string& backroundTextureFilePath, const std::string& rTextureFilePath, const std::string& gTextureFilePath, const std::string& bTextureFilePath, const std::string& blendMapFilePath) : _terrainSize(size), _vertexCount(unsigned int(0.16*_terrainSize)), _texture(nullptr), _terrainTexture(nullptr), _backroundTexturePath(backroundTextureFilePath), _rTexturePath(rTextureFilePath), _gTexturePath(gTextureFilePath), _bTexturePath(bTextureFilePath), _blendMapTexturePath(blendMapFilePath)
{
	this->_mesh = new HMEngine::Core::Mesh();
	int count = this->_vertexCount * this->_vertexCount;
	this->GenerateTerrain();
}

HMEngine::Components::TerrainRenderer::TerrainRenderer(unsigned int size, const std::string& backroundTextureFilePath) : _terrainSize(size), _vertexCount(unsigned int(1.6f*size)), _texture(nullptr), _terrainTexture(nullptr), _backroundTexturePath(backroundTextureFilePath), _rTexturePath(""), _gTexturePath(""), _bTexturePath(""), _blendMapTexturePath("")
{
	this->_mesh = new HMEngine::Core::Mesh();
	int count = this->_vertexCount * this->_vertexCount;
	this->GenerateTerrain();
}

HMEngine::Components::TerrainRenderer::TerrainRenderer(unsigned int size, float maxHeight, const std::string& heightMapPath, const std::string& texturePath) : _terrainSize(size), _texture(nullptr), _terrainTexture(nullptr), _backroundTexturePath(texturePath), _maxHeight(unsigned int(maxHeight))
{
	this->_mesh = new HMEngine::Core::Mesh();
	this->GenerateTerrain(heightMapPath);
}

HMEngine::Components::TerrainRenderer::TerrainRenderer(unsigned int size, float maxHeight, const std::string& heightMapPath, const std::string& backroundTextureFilePath, const std::string& rTextureFilePath, const std::string& gTextureFilePath, const std::string& bTextureFilePath, const std::string& blendMapFilePath) : _terrainSize(size), _texture(nullptr), _terrainTexture(nullptr), _maxHeight(unsigned int(maxHeight)), _backroundTexturePath(backroundTextureFilePath), _rTexturePath(rTextureFilePath), _gTexturePath(gTextureFilePath), _bTexturePath(bTextureFilePath), _blendMapTexturePath(blendMapFilePath)
{
	this->_mesh = new HMEngine::Core::Mesh();
	this->GenerateTerrain(heightMapPath);
}

HMEngine::Components::TerrainRenderer::~TerrainRenderer()
{
	delete this->_mesh;
	if (this->_isAttachedToGameObject)
	{
		HMEngine::Core::Rendering::RenderingEngine::GetInstance().RemoveTerrainRenderer(*this);
		if (this->_rTexturePath != "")
			delete this->_terrainTexture;
		else
			delete this->_texture;
	}
}

HMEngine::Components::TerrainRenderer::TerrainRenderer(const HMEngine::Components::TerrainRenderer& other)
{
	this->_backroundTexturePath = other._backroundTexturePath;
	this->_rTexturePath = other._rTexturePath;
	this->_gTexturePath = other._gTexturePath;
	this->_bTexturePath = other._bTexturePath;
	this->_blendMapTexturePath = other._blendMapTexturePath;
	this->_maxHeight = other._maxHeight;
	this->_mesh = new HMEngine::Core::Mesh(*other._mesh);
	if (other._isAttachedToGameObject)
	{
		if (other._texture != nullptr)
			this->_texture = new HMEngine::OpenGL::Texture(*other._texture);
		else
			this->_terrainTexture = new HMEngine::OpenGL::TerrainTexture(*other._terrainTexture);
		this->_isAttachedToGameObject = other._isAttachedToGameObject;

		HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddTerrainRenderer(*this);
	}
}

HMEngine::Components::TerrainRenderer& HMEngine::Components::TerrainRenderer::operator=(const HMEngine::Components::TerrainRenderer& other)
{
	if (this != &other)
	{
		this->_backroundTexturePath = other._backroundTexturePath;
		this->_rTexturePath = other._rTexturePath;
		this->_gTexturePath = other._gTexturePath;
		this->_bTexturePath = other._bTexturePath;
		this->_blendMapTexturePath = other._blendMapTexturePath;
		this->_maxHeight = other._maxHeight;
		delete this->_mesh;
		this->_mesh = new HMEngine::Core::Mesh(*other._mesh);
		if (other._isAttachedToGameObject)
		{
			if (other._texture != nullptr)
			{
				delete this->_texture;
				this->_texture = new HMEngine::OpenGL::Texture(*other._texture);
			}
			else
			{
				delete this->_terrainTexture;
				this->_terrainTexture = new HMEngine::OpenGL::TerrainTexture(*other._terrainTexture);
			}
			this->_terrainTexture = new HMEngine::OpenGL::TerrainTexture(*other._terrainTexture);
			this->_isAttachedToGameObject = other._isAttachedToGameObject;
			HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddTerrainRenderer(*this);
		}
	}

	return *this;
}

void HMEngine::Components::TerrainRenderer::AttachToGameObjectEvent()
{
	if (this->_rTexturePath != "")
		this->_terrainTexture = new HMEngine::OpenGL::TerrainTexture(this->_backroundTexturePath, this->_rTexturePath, this->_gTexturePath, this->_bTexturePath, this->_blendMapTexturePath);
	else
		this->_texture = new HMEngine::OpenGL::Texture(this->_backroundTexturePath, GL_RGB);
	HMEngine::Core::Rendering::RenderingEngine::GetInstance().AddTerrainRenderer(*this);
	//this->_mesh->InitBuffers();
}

void HMEngine::Components::TerrainRenderer::BindTextures() const
{
	if (this->_terrainTexture != nullptr)
		this->_terrainTexture->Bind();
	else
		this->_texture->Bind();
}

void HMEngine::Components::TerrainRenderer::DrawTerrain() const
{
	this->BindTextures(); //Binds terrain textures
	this->_mesh->Draw();
}

void HMEngine::Components::TerrainRenderer::GenerateTerrain()
{
	int count = this->_vertexCount * this->_vertexCount;
	float* normals = new float[count * 3];
	int vertexPointer = 0;
	for (unsigned int i = 0; i < this->_vertexCount; i++)
	{
		for (unsigned int j = 0; j < this->_vertexCount; j++)
		{
			this->_mesh->AddVertex(glm::vec3(float(j) / ((float)this->_vertexCount - 1) * this->_terrainSize, 0, (float)i / ((float)this->_vertexCount - 1) * this->_terrainSize));
			this->_mesh->AddNormal(glm::vec3(0, 1, 0));
			this->_mesh->AddUV(glm::vec2((float)j / ((float)this->_vertexCount - 1), (float)i / ((float)this->_vertexCount - 1)) *= 40);
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (unsigned int gz = 0; gz < this->_vertexCount - 1; gz++)
	{
		for (unsigned int gx = 0; gx < this->_vertexCount - 1; gx++)
		{
			int topLeft = (gz * this->_vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * this->_vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			this->_mesh->AddIndex(topLeft);
			this->_mesh->AddIndex(bottomLeft);
			this->_mesh->AddIndex(topRight);
			this->_mesh->AddIndex(topRight);
			this->_mesh->AddIndex(bottomLeft);
			this->_mesh->AddIndex(bottomRight);
		}
	}

	delete normals;
}

void HMEngine::Components::TerrainRenderer::GenerateTerrain(const std::string& heightMapPath)
{
	cv::Mat img;
	try //tries to read the image
	{
		img = cv::imread(heightMapPath);
	}
	catch (const std::exception& e)
	{
		HMEngine::Core::Utilities::ThrowException(e.what());
	}
	this->_vertexCount = img.rows;

	int count = this->_vertexCount * this->_vertexCount;
	int vertexPointer = 0;
	for (unsigned int i = 0; i < this->_vertexCount; i++)
	{
		for (unsigned int j = 0; j < this->_vertexCount; j++)
		{
			this->_mesh->AddVertex(glm::vec3(float(j) / ((float)this->_vertexCount - 1) * this->_terrainSize, this->GetHeightFromPixel(img, j, i), (float)i / ((float)this->_vertexCount - 1) * this->_terrainSize));
			this->_mesh->AddNormal(this->CalculateNormal(img, j, i));
			this->_mesh->AddUV(glm::vec2((float)j / ((float)this->_vertexCount - 1), (float)i / ((float)this->_vertexCount - 1)) *= 40);
			vertexPointer++;
		}
	}

	int pointer = 0;
	for (unsigned int gz = 0; gz < this->_vertexCount - 1; gz++)
	{
		for (unsigned int gx = 0; gx < this->_vertexCount - 1; gx++)
		{
			int topLeft = (gz * this->_vertexCount) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * this->_vertexCount) + gx;
			int bottomRight = bottomLeft + 1;
			this->_mesh->AddIndex(topLeft);
			pointer++;
			this->_mesh->AddIndex(bottomLeft);
			pointer++;
			this->_mesh->AddIndex(topRight);
			pointer++;
			this->_mesh->AddIndex(topRight);
			pointer++;
			this->_mesh->AddIndex(bottomLeft);
			pointer++;
			this->_mesh->AddIndex(bottomRight);
			pointer++;
		}
	}
}

float HMEngine::Components::TerrainRenderer::GetHeightFromPixel(const cv::Mat& image, unsigned int x, unsigned int y)
{
	float height = 0;
	if (x < 0U || x >= unsigned int(image.rows) || y < 0U || y >= unsigned int(image.rows))
	{
		return 0;
	}

	cv::Vec3b pixel = image.at<cv::Vec3b>(x, y);

	int color = ~(256 * 256 * pixel[2] + 256 * pixel[1] + pixel[0]) + 1;
	height = float(color);
	height += HMEngine::Components::TerrainRenderer::MAX_PIXEL_COLOR / 2.0f;
	height /= HMEngine::Components::TerrainRenderer::MAX_PIXEL_COLOR / 2.0f;
	height *= this->_maxHeight;

	return height * -1;
}

glm::vec3 HMEngine::Components::TerrainRenderer::CalculateNormal(const cv::Mat & image, unsigned int x, unsigned int y)
{
	float heightL = this->GetHeightFromPixel(image, x - 1, y);
	float heightR = this->GetHeightFromPixel(image, x + 1, y);
	float heightD = this->GetHeightFromPixel(image, x, y - 1);
	float heightU = this->GetHeightFromPixel(image, x, y + 1);

	return glm::normalize(glm::vec3(heightL - heightR, 2.0f, heightD - heightU));
}
