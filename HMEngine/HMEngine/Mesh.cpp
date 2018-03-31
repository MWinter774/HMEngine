#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "Utilities.h"
#include "InvalidMeshFileException.h"
#include "assimp\scene.h"
#include "assimp\Importer.hpp"
#include "assimp\postprocess.h"

HMEngine::Core::Mesh::Mesh()
{
	this->_meshPhysicalData.center = glm::vec3(-999,-999,-999);
	this->_meshPhysicalData.radius = -1.0f;
}

HMEngine::Core::Mesh::Mesh(const std::string& path) : _numIndices(0)
{
	this->Load(path);
	this->InitBuffers();

	auto[center, radius] = HMEngine::Core::Mesh::GetRadiusAndCenterFromMesh(this->_vertices);
	this->_meshPhysicalData.center = center;
	this->_meshPhysicalData.radius = radius;
}

HMEngine::Core::Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& normals, const std::vector<GLuint>& indices) : _numIndices(0), _vertices(vertices), _uvs(uvs), _normals(normals), _indices(indices)
{
	this->InitBuffers();

	auto[center, radius] = HMEngine::Core::Mesh::GetRadiusAndCenterFromMesh(this->_vertices);
	this->_meshPhysicalData.center = center;
	this->_meshPhysicalData.radius = radius;
}

HMEngine::Core::Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& normals) : _numIndices(0), _vertices(vertices), _uvs(uvs), _normals(normals)
{
	this->InitBuffers();

	auto[center, radius] = HMEngine::Core::Mesh::GetRadiusAndCenterFromMesh(this->_vertices);
	this->_meshPhysicalData.center = center;
	this->_meshPhysicalData.radius = radius;
}

HMEngine::Core::Mesh::Mesh(const HMEngine::Core::Mesh& other) : _meshPhysicalData(other._meshPhysicalData)
{
	this->_vertices = other._vertices;
	this->_normals = other._normals;
	this->_uvs = other._uvs;
	this->_indices = other._indices;

	this->InitBuffers();
}

HMEngine::Core::Mesh::~Mesh()
{
	glBindVertexArray(this->_vao);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDeleteBuffers(NUM_BUFFERS, this->_vbo);
	glDeleteBuffers(1, &this->_vao);
	glBindVertexArray(0);
}

void HMEngine::Core::Mesh::Load(const std::string& path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile((path).c_str(),
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace);

	if (!scene)
	{
		throw HMEngine::Exceptions::InvalidMeshFileException("OBJECT FILE: " + path + " DOESN'T EXIST!!");
		return;
	}

	const aiMesh* model = scene->mMeshes[0];

	const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
	for (unsigned int i = 0; i < model->mNumVertices; i++)
	{
		const aiVector3D pos = model->mVertices[i];
		const aiVector3D normal = model->mNormals[i];
		const aiVector3D texCoord = model->HasTextureCoords(0) ? model->mTextureCoords[0][i] : aiZeroVector;
		if (model->mTangents != nullptr)
			const aiVector3D tangent = model->mTangents[i];

		this->_vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
		this->_uvs.push_back(glm::vec2(texCoord.x, texCoord.y));
		this->_normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
	}

	for (unsigned int i = 0; i < model->mNumFaces; i++)
	{
		const aiFace& face = model->mFaces[i];
		assert(face.mNumIndices == 3);
		this->_indices.push_back(face.mIndices[0]);
		this->_indices.push_back(face.mIndices[1]);
		this->_indices.push_back(face.mIndices[2]);
	}
}

const std::vector<std::string> HMEngine::Core::Mesh::SplitString(std::string& str)
{
	//split the string to a vector of strings, delimited by ' '
	std::istringstream iss(str);
	std::vector<std::string> tokens{ std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{} };
	return tokens;
}

HMEngine::Core::Mesh& HMEngine::Core::Mesh::operator=(HMEngine::Core::Mesh& other)
{
	if (this != &other)
	{
		/* Sets the new vertices, normals, uvs and indices */
		this->_vertices = other._vertices;
		this->_normals = other._normals;
		this->_uvs = other._uvs;
		this->_indices = other._indices;

		this->_meshPhysicalData = other._meshPhysicalData;

		/* Gets rid of old buffers */
		glBindVertexArray(this->_vao);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDeleteBuffers(2, this->_vbo);
		glDeleteBuffers(1, &this->_vao);

		/* Generate new ones with the new values */
		this->InitBuffers();
	}

	return *this;
}

void HMEngine::Core::Mesh::Draw()
{
	if (this->_indices.size() > 0)
	{
		glBindVertexArray(this->_vao);

		glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glBindVertexArray(this->_vao);

		glDrawArrays(GL_TRIANGLES, 0, this->_vertices.size());
	}
}

std::pair<glm::vec3, float> HMEngine::Core::Mesh::GetRadiusAndCenterFromMesh(const std::vector<glm::vec3>& vertices)
{
	std::vector<float> coords;
	std::vector<Seb::Point<float>> points;
	glm::vec3 center;
	float radius;
	Seb::Smallest_enclosing_ball<float>* miniball;

	for (auto& vertex : vertices)
	{
		coords.push_back(vertex.x);
		coords.push_back(vertex.y);
		coords.push_back(vertex.z);

		points.push_back(Seb::Point<float>(3, coords.begin()));

		coords.clear();
	}
	miniball = new Seb::Smallest_enclosing_ball<float>(3, points);
	radius = miniball->radius();

	/* Initializes the center */
	float tempCenter[3] = { 0.0f };
	float* centerBegin = miniball->center_begin();
	float* centerEnd = miniball->center_end();
	for (unsigned int i = 0; i < 3 && centerBegin != centerEnd; i++)
	{
		tempCenter[i] = *centerBegin++;
	}
	center = glm::vec3(tempCenter[0], tempCenter[1], tempCenter[2]);

	return std::pair<glm::vec3, float>(center, radius);
}

void HMEngine::Core::Mesh::InitBuffers()
{
	glGenVertexArrays(1, &this->_vao);
	glBindVertexArray(this->_vao);

	glGenBuffers(NUM_BUFFERS, this->_vbo);

	/* Generates the vertices buffer */
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(this->_vertices[0]), &this->_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/* Generates the uvs buffer */
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_TEXTURE_COORDS]);
	glBufferData(GL_ARRAY_BUFFER, (this->_uvs.size() * sizeof(this->_uvs[0])), &this->_uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	/* Generates the normals buffer */
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_NORMALS]);
	glBufferData(GL_ARRAY_BUFFER, (this->_normals.size() * sizeof(this->_normals[0])), &this->_normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	/* Generates the indices buffer */
	if (this->_indices.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo[VBO_INDICES]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (this->_indices.size() * sizeof(this->_indices[0])), &this->_indices[0], GL_STATIC_DRAW);
	}
}