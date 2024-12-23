#pragma once
#include <vector>
#include "Vertex.h"
#include <string>
#include <fstream>
#include <iostream>
#include "Object.h"

class ObjParser
{
public:
	std::string name;
	std::vector<Vertex> allVertices;
	std::vector<std::vector<Vertex>> faceData;

	std::vector<Object*> objectList = {};

	std::ifstream file;
	std::string str;

	void openObj(const char path[]) {
		file = std::ifstream(path);
	}

	void load() {
		name = "";
		allVertices = std::vector<Vertex>();
		faceData = std::vector <std::vector<Vertex>>();


		loadVertices();

		std::string keyword;
		Object* newObject = new Object();;
		while (std::getline(file, str)) {
			// Output the text from the file
			if (str.at(0) != '#') {
				keyword = getToken(str, 0);

				if (keyword == "o")
				{
					//object
					newObject = new Object();
					newObject->name = getToken(str, 2);
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

						if(vertexIndex < allVertices.size())
						{
							Vertex faceVertex = allVertices[vertexIndex];
							faceVertices.push_back(faceVertex);
						}
					}

					// and insert data into object
					newObject->faceData.push_back(faceVertices);
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
			}
		}

		file.clear();
		file.seekg(0);
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

