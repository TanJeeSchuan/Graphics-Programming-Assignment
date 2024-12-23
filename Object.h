#pragma once
#include <vector>
#include "Vertex.h"
#include <string>

class Object
{	
public:
	//std::vector<Vertex> vertices;
	std::string name;

	std::vector<std::vector<Vertex>> faceData;		//directly input vertex data """"DO NOT INPUT INDEX""""


	//std::vector<std::vector<float>> getVerticesOfFace(std::vector<int> faceData)
	//{
	//	return nullptr;
	//}

	//std::vector<float> getVertexByIndex(int index)
	//{

	//}
};

