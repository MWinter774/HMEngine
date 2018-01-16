#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>

HMEngine::Core::Mesh::Mesh(const std::string& path) : _numIndices(0)
{
	this->Load(path);
	this->InitBuffers();
}

HMEngine::Core::Mesh::Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& uvs, const std::vector<glm::vec3>& normals) : _numIndices(0), _vertices(vertices), _uvs(uvs), _normals(normals)
{
	this->InitBuffers();
}

HMEngine::Core::Mesh::~Mesh()
{
	glBindVertexArray(this->_vao);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDeleteBuffers(2, this->_vbo);
	glDeleteBuffers(1, &this->_vao);
	glBindVertexArray(0);
}

void HMEngine::Core::Mesh::Load(const std::string& path)
{
	std::ifstream file(path.c_str());
	std::string line;
	std::vector<std::string> tokens;
	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);

			if (line.length() > 2)
			{
				const char* lineC = line.c_str();
				switch (lineC[0])
				{
				case 'v':
					if (lineC[1] == 't')
					{
						tokens = SplitString(line);
						if (tokens.size() == 3)
							this->_tempUvs.push_back(glm::vec2(std::stof(tokens[1]), std::stof(tokens[2])));
					}
					else if (lineC[1] == 'n')
					{
						tokens = SplitString(line);
						if (tokens.size() == 4)
							this->_tempNormals.push_back(glm::vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])));
					}
					else
					{
						tokens = SplitString(line);
						if (tokens.size() == 4)
							this->_tempVertices.push_back(glm::vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])));
					}

					break;
				case 'f':
					std::replace(line.begin(), line.end(), '/', ' ');
					tokens = SplitString(line);
					if (tokens.size() == 10)
					{
						fIndices f1
						{
							std::stoi(tokens[1]),std::stoi(tokens[2]),std::stoi(tokens[3]),
						};
						fIndices f2
						{
							std::stoi(tokens[4]), std::stoi(tokens[5]), std::stoi(tokens[6]),
						};
						fIndices f3
						{
							std::stoi(tokens[7]), std::stoi(tokens[8]), std::stoi(tokens[9]),
						};
						this->_fIndices.push_back(f1);
						this->_fIndices.push_back(f2);
						this->_fIndices.push_back(f3);
					}
					break;
				}
			}
		}
		this->_numIndices = this->_fIndices.size();

		for (int i = 0; i < this->_numIndices; i++)
		{
			this->_vertices.push_back(this->_tempVertices[this->_fIndices[i].vertexIndex - 1]);
			this->_uvs.push_back(this->_tempUvs[this->_fIndices[i].textureIndex - 1]);
			this->_normals.push_back(this->_tempNormals[this->_fIndices[i].normalIndex - 1]);
		}
		file.close();
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
		this->_vertices = other._vertices;
		this->_normals = other._normals;
		this->_uvs = other._uvs;
		this->_fIndices = other._fIndices;
	}

	return *this;
}

void HMEngine::Core::Mesh::Draw()
{
	glBindVertexArray(this->_vao);

	glDrawArrays(GL_TRIANGLES, 0, this->_vertices.size());

	glBindVertexArray(0);
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

	/* Generates the uv's buffer */
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_TEXTURE_COORDS]);
	glBufferData(GL_ARRAY_BUFFER, (this->_uvs.size() * sizeof(this->_uvs[0])), &this->_uvs[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//set normals buffer.
	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[VBO_NORMALS]);
	glBufferData(GL_ARRAY_BUFFER, (this->_normals.size() * sizeof(this->_normals[0])), &this->_normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);


	/* Generates the indices buffer */
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_vbo[VBO_INDICES]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, (this->_mesh->GetFaceIndices * 3 * sizeof(this->_mesh->GetFaceIndices()[0].vertexIndex[0])), &this->_mesh->GetFaceIndices[, GL_STATIC_DRAW);
}