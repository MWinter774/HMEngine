#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>


HMEngine::Core::Mesh::Mesh(const std::string& path)
{
	this->Load(path);
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
	this->_vertices = other.GetVertices();
	this->_normals = other.GetNormals();
	this->_uvs = other.GetUVs();
	this->_fIndices = other.GetFaceIndices();

	return *this;
}