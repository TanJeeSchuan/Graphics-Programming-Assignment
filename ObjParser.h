#pragma once
#include <vector>
#include "Vertex.h"
#include <string>
#include <fstream>
#include <iostream>
#include "Object.h"
#include "Material.h"

class ObjParser
{
public:
	std::string name;
	std::vector<Vertex> allVertices;
	std::vector<std::vector<float>> allNormals;
	std::vector<std::vector<Vertex>> faceData;

	std::vector<Material*> materialList = {};

	std::vector<Object*> objectList = {};

	std::ifstream file;
	std::ifstream mtlFile;
	std::string str;

	void openObj(const char path[]) {
		file = std::ifstream(path);
	}

	void openMtl(const char path[]) {
		mtlFile = std::ifstream(path);
	}

	void loadMaterial() {
		std::string keyword;
		Material* newMaterial = new Material();;

		while (std::getline(mtlFile, str)) {
			// Output the text from the file
			if (str.size() > 0 && str.at(0) != '#') {
				keyword = getToken(str, 0);

				if (keyword == "newmtl") {
					newMaterial = new Material();
					newMaterial->name = getTokens(str)[1];

					materialList.push_back(newMaterial);
				}

				else if (keyword == "Ns") {
					newMaterial->setShininess(std::stof(getTokens(str)[1]));
				}

				else if (keyword == "Ka") {
					auto values = getTokens(str);
					newMaterial->setAmbientColour(std::stof(values[1]), std::stof(values[2]), std::stof(values[3]));
				}

				else if (keyword == "Kd") {
					auto values = getTokens(str);
					newMaterial->setDiffuseColour(std::stof(values[1]), std::stof(values[2]), std::stof(values[3]));
				}

				else if (keyword == "Ks") {
					auto values = getTokens(str);
					newMaterial->setSpecularColour(std::stof(values[1]), std::stof(values[2]), std::stof(values[3]));
				}

				else if (keyword == "Ke") {
					//auto values = getTokens(str);
					//newMaterial->setAmbientColour(std::stof(values[1]), std::stof(values[2]), std::stof(values[3]));
				}

				else if (keyword == "Ni") {

				}

				else if (keyword == "d") {

				}
			}
		}
	}

	void load() {
		name = "";
		allVertices = std::vector<Vertex>();
		faceData = std::vector <std::vector<Vertex>>();

		Material* currentMaterial = nullptr;

		loadVertices();

		std::string keyword;
		Object* newObject = new Object();;
		while (std::getline(file, str)) {
			// Output the text from the file
			if (str.size() > 0 && str.at(0) != '#') {
				keyword = getToken(str, 0);

				if (keyword == "o")
				{
					//object
					newObject = new Object();
					newObject->name = getTokens(str)[1];

					currentMaterial = nullptr;

					objectList.push_back(newObject);
				}

				//else if (keyword == "v") {
				//	auto tokens = getTokens(str);
				//	loadVertex(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
				//}

				else if (keyword == "f") {
					//face
					std::vector<Vertex> faceVertices = {};
					auto tokens = getTokens(str);
					
					for (int i = 1; i < tokens.size(); i++)
					{
						auto verts = tokens[i];		// f 1/2/3 5/3/1 1/8/4 5/6/1

						//convert to vertex object
						int vertexIndex = std::stoi(split(verts, '/')[0]) - 1;
						std::cout << vertexIndex << std::endl;

						Vertex faceVertex;
						if(vertexIndex < allVertices.size())
						{
							faceVertex = allVertices[vertexIndex];
							faceVertex.material = currentMaterial;
						}

						//-------------- normal vertex --------------
						int normalIndex = std::stoi(split(verts, '/')[2]) - 1;
						std::cout << normalIndex << std::endl;

						if (normalIndex < allNormals.size())
						{
							auto normalVerts = allNormals[normalIndex];
							faceVertex.normX = normalVerts[0];
							faceVertex.normY = normalVerts[1];
							faceVertex.normZ = normalVerts[2];
						}

						faceVertices.push_back(faceVertex);
					}

					// and insert data into object
					newObject->faceData.push_back(faceVertices);
				}

				else if (keyword == "usemtl") {
					//find in materials list by name
					for (auto mat : materialList) {
						if (mat->name == getTokens(str)[1]) {
							//assign to var
							currentMaterial = mat;
						}
					}

					
					//current object will use this material until reassigned or object data ends
				}
			}
		}
	}

	void loadVertices() {
		std::string keyword;
		while (std::getline(file, str)) {
			if (str.at(0) != '#') // if not comment
			{
				keyword = getToken(str, 0);
				if (keyword == "v") {
					auto tokens = getTokens(str);
					loadVertex(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
				}

				else if (keyword == "vn") {
					auto tokens = getTokens(str);
					loadNormal(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
				}
			}
		}

		file.clear();
		file.seekg(0);
	}

	void loadNormal(float x, float y, float z) {
		allNormals.push_back({ x,y,z });
	}

	void loadVertex(float x, float y, float z)
	{
		allVertices.push_back(Vertex(x, y, z));
	}

private:
	std::string getToken(std::string str, int index)
	{
		int occurance = index;
		std::string outStr = "";
		char c;

		for (int i = 0; i < str.size(); i++) {
			c = str.at(i);
			if (c == ' ') {
				if (occurance == index)
					break;
				else
					occurance++;
			}
			else
				outStr.push_back(c);
		}

		return outStr;
	}

	std::vector<std::string> getTokens(std::string str) {
		std::vector<std::string> outVec = {};
		std::string outStr = "";
		char c;

		for (int i = 0; i < str.size(); i++) {
			c = str.at(i);
			if (c != ' ')
			{
				outStr.push_back(c);
				if (i == str.size() - 1)
					outVec.push_back(outStr);
			}
			else {
				outVec.push_back(outStr);
				outStr = "";
			}


		}

		return outVec;
	}

	std::vector<std::string> split(std::string str, char delimitter) {
		std::vector<std::string> outVec = {};
		std::string outStr = "";
		char c;

		for (int i = 0; i < str.size(); i++) {
			c = str.at(i);
			if (c != delimitter)
			{
				outStr.push_back(c);
				if (i == str.size() - 1)
					outVec.push_back(outStr);
			}
			else {
				outVec.push_back(outStr);
				outStr = "";
			}


		}

		return outVec;
	}
};

