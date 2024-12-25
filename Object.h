#pragma once
#include <vector>
#include "Vertex.h"
#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Object
{	
public:
	//std::vector<Vertex> vertices;
	std::string name;

	std::vector<std::vector<Vertex>> faceData;		//directly input vertex data """"DO NOT INPUT INDEX""""

	Object* parent;
	std::vector<Object*> children;

	glm::mat4x4 transform = glm::mat4x4(1.0f);

	Vertex localPosition;
	Vertex origin;

	void calculateOrigin()
	{
		float vertNum = 0;
		int centerX = 0, centerY = 0, centerZ = 0;
		
		for (auto face : faceData) {
			for (auto& vertex : face) {
				centerX += vertex.x;
				centerY += vertex.y;
				centerZ += vertex.z;
				vertNum++;
			}
		}

		

		origin.x = centerX / vertNum;
		origin.y = centerY / vertNum;
		origin.z = centerZ / vertNum;

		localPosition.x = origin.x;
		localPosition.y = origin.y;
		localPosition.z = origin.z;

		glm::translate(transform, glm::vec3(origin.x, origin.y, origin.z));
	}

	void transformToWorldPositionZero() {
		for (int i  = 0; i < faceData.size(); i++) {
			auto face = &faceData[i];
			
			for (int j = 0; j < face->size(); j++) {
				Vertex* vertex = &face->at(j);
				vertex->x -= origin.x;
				vertex->y -= origin.y;
				vertex->z -= origin.z;
			}
		}

		return;
	}

	Vertex getWorldSpace() {
		Vertex result;

		auto currentObject = this;

		while (currentObject != nullptr) {
			result = result + currentObject->localPosition;
			currentObject = currentObject->parent;
		}

		return result;
	}

	void addParent(Object* parentObject) {
		localPosition = -parentObject->localPosition + localPosition;
	}

	//std::vector<std::vector<float>> getVerticesOfFace(std::vector<int> faceData)
	//{
	//	return nullptr;
	//}

	//std::vector<float> getVertexByIndex(int index)
	//{

	//}
};

