#pragma once

#include <iostream>

#include <vector>
#include "Vertex.h"
#include <string>

#define GLM_ENABLE_EXPERIMENTAL 1

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtc/quaternion.hpp"

#include "glm/gtc/matrix_inverse.hpp"

class Object
{	
private:
	glm::mat4x4 transform = glm::mat4x4(1.0f);

public:
	//std::vector<Vertex> vertices;
	std::string name;

	std::vector<std::vector<Vertex>> faceData;		//directly input vertex data """"DO NOT INPUT INDEX""""

	Object* parent;
	std::vector<Object*> children;


	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scaling = { 1,1,1 };

	Vertex origin;

	void translate(float x, float y, float z) {
		transform = glm::translate(transform, glm::vec3(x, y, z));
	}

	void scale(float x, float y, float z) {
		transform = glm::scale(transform, glm::vec3(x, y, z));
	}

	void rotate(float angle, float x, float y, float z) {
		transform = glm::rotate(transform, angle, glm::vec3(x, y, z));
	}

	void setRotation(float angle, float x, float y, float z) {
		auto maxRadian = 2 * glm::pi<float>();
		float newAngle = angle;
		if (angle > maxRadian) {
			newAngle = angle - floor(angle / maxRadian) * maxRadian;
		}
		std::cout << newAngle << "\n";

		transform = transform * glm::inverse(glm::mat4_cast(glm::quat(transform)));		//remove initial rotation 
		transform = glm::rotate(transform, newAngle, glm::vec3(x, y, z));
	}

	glm::mat4 getTransform() {
		//glm::vec3 eulerRotation = glm::degrees(glm::eulerAngles(rotation));

		//glm::mat4x4 t = glm::mat4x4(1.0f);
		//t = glm::translate(t, glm::vec3(position.x, position.y, position.z));
		////t = glm::translate(t, glm::vec3);
		//t = glm::rotate(eulerRotation.x, glm::vec3(1, 0, 0));
		//t = glm::rotate(eulerRotation.y, glm::vec3(0, 1, 0));
		//t = glm::rotate(eulerRotation.z, glm::vec3(0, 0, 1));
		//t = glm::scale(t, scaling);

		return transform;
	}


	glm::mat4 getWorldTransform() {
		auto current = this;
		glm::mat4x4 newTransform = glm::mat4x4(1.0f);
		while (current != nullptr) {
			newTransform = current->getTransform() * newTransform;
			current = current->parent;
		}

		return newTransform;
	}

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

		position.x = origin.x;
		position.y = origin.y;
		position.z = origin.z;

		//localPosition.x = origin.x;
		//localPosition.y = origin.y;
		//localPosition.z = origin.z;

		transform = glm::translate(transform, glm::vec3(origin.x, origin.y, origin.z));
		// 
		//transform = glm::scale(transform, glm::vec3(1, 1, 1));
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

	//-------------------------

	void addParent(Object* parentObject) {
		if (this->parent != nullptr) {
			parent->removeChild(this);
		}
		parent = parentObject;
		parentObject->children.push_back(this);
	}

	void addChild(Object* childObject) {
		if (childObject->parent != nullptr) {
			childObject->parent->removeChild(childObject);
		}

		childObject->parent = this;
		childObject->transform = glm::inverse(this->getWorldTransform()) * childObject->transform;

		this->children.push_back(childObject);
	}

	void removeChild(Object* child) {
		this->children.erase(std::find(children.begin(), children.end(), child));
	}
};

