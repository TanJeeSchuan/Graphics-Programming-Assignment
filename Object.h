#pragma once
#include <vector>
#include "Vertex.h"
#include <string>

#define GLM_ENABLE_EXPERIMENTAL 1

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtc/quaternion.hpp"


class Object
{	
public:
	//std::vector<Vertex> vertices;
	std::string name;

	std::vector<std::vector<Vertex>> faceData;		//directly input vertex data """"DO NOT INPUT INDEX""""

	Object* parent;
	std::vector<Object*> children;

	glm::mat4x4 transform = glm::mat4x4(1.0f);

	//do not modify directly
	glm::vec3 scale = glm::vec3(1.0f);
	glm::quat rotation = glm::quat();
	glm::vec3 translation = glm::vec3(1.0f);
	glm::vec3 skew;
	glm::vec4 perspective;

	//Vertex localPosition;
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

		//localPosition.x = origin.x;
		//localPosition.y = origin.y;
		//localPosition.z = origin.z;

		transform = glm::translate(transform, glm::vec3(origin.x, origin.y, origin.z));
		transform = glm::scale(transform, glm::vec3(1, 1, 1));
	}

	void translate(float x, float y, float z) {
		transform = glm::translate(transform, glm::vec3(x, y, z));
	}

	void getWorldTransform() {
		auto current = this;
		glm::vec3 scale = glm::vec3(1.0f);
		glm::quat rotation = glm::quat();
		glm::vec3 translation = glm::vec3(1.0f);
		glm::vec3 skew;
		glm::vec4 perspective;

		glm::mat4x4 newTransform = glm::mat4x4(1.0f);
		while (current != nullptr) {
			newTransform = current->transform * newTransform;

			//current->calculateTransforms();

			//scale *= current->scale;
			//rotation *= current->rotation;
			//translation *= current->translation;
			//skew *= current->skew;
			//perspective *= current->perspective;

			current = current->parent;
		}

		glm::decompose(newTransform, scale, rotation, translation, skew, perspective);
		this->scale			= scale;
		this->rotation		= rotation;
		this->translation	= translation;
		this->skew			= skew;
		this->perspective	= perspective;
	}

	void calculateTransforms() {
		glm::decompose(transform, scale, rotation, translation, skew, perspective);
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

	//Vertex getWorldSpace() {
	//	Vertex result;

	//	auto currentObject = this;

	//	while (currentObject != nullptr) {
	//		result = result + currentObject->localPosition;
	//		currentObject = currentObject->parent;
	//	}

	//	return result;
	//}

	void addParent(Object* parentObject) {
		parent = parentObject;
		parentObject->children.push_back(this);
		//transform = transform * parentObject->transform;
		/*localPosition = -parentObject->localPosition + localPosition;*/
	}

	//std::vector<std::vector<float>> getVerticesOfFace(std::vector<int> faceData)
	//{
	//	return nullptr;
	//}

	//std::vector<float> getVertexByIndex(int index)
	//{

	//}
};

