#pragma once

#include <iostream>

#include <vector>
#include "Vertex.h"
#include <string>
#include <algorithm>

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
	bool enabled = true;

	//std::vector<Vertex> vertices;
	std::string name;

	std::vector<std::vector<Vertex>> faceData;		//directly input vertex data """"DO NOT INPUT INDEX""""

	Object* parent;
	std::vector<Object*> children;


	//glm::vec3 position;
	//glm::quat rotation;
	//glm::vec3 scaling = { 1,1,1 };

	Vertex origin;

	glm::vec3 getWorldOrigin() {
		glm::vec3 vec = { origin.x, origin.y, origin.z };
		vec += glm::vec3(transform[3]);
		return vec;
	}

	void translate(float x, float y, float z) {
		origin.x += x;
		origin.y += y;
		origin.z += z;
		transform = glm::translate(transform, glm::vec3(origin.x, origin.y, origin.z));
	}

	void scale(float x, float y, float z) {
		transform = glm::scale(transform, glm::vec3(x, y, z));
	}

	float rot = 0.;
	void rotate(float angle, float x, float y, float z) {
		auto inDegrees = glm::degrees(angle);

		inDegrees = fmod(inDegrees, 360.f);

		auto newAngle = glm::radians(inDegrees);
		
		auto t1 = glm::translate(glm::mat4(1), -glm::vec3(origin.x, origin.y, origin.z));
		auto r1 = glm::rotate(glm::mat4(1), newAngle, glm::normalize(glm::vec3(x, y, z)));
		auto t2 = glm::translate(glm::mat4(1), glm::vec3(origin.x, origin.y, origin.z));

		//transform = r1 * transform;
		transform = t2 * r1 * t1 * transform;
	}

	void setRotation(float angle, float x, float y, float z) {
		auto maxRadian = 2 * glm::pi<float>();
		float newAngle = angle;
		if (angle > maxRadian) {
			newAngle = angle - floor(angle / maxRadian) * maxRadian;
		}
		transform = transform * glm::inverse(glm::mat4_cast(glm::quat(transform)));		//remove initial rotation 

		transform = glm::rotate(transform, newAngle, glm::vec3(x, y, z));
	}

	glm::mat4 getTransform() {
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

	void setOrigin(float x, float y, float z) {
		origin.x = x;
		origin.y = y;
		origin.z = z;
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

		//---- new ---- median
		//std::vector<float> xVerts;
		//std::vector<float> yVerts;
		//std::vector<float> zVerts;

		//for (auto face : faceData) {
		//	for (auto& vertex : face) {
		//		xVerts.push_back(vertex.x);
		//		yVerts.push_back(vertex.y);
		//		zVerts.push_back(vertex.z);
		//		vertNum++;
		//	}
		//}

		//if (xVerts.empty() || yVerts.empty() || zVerts.empty()) {
		//	return;
		//}

		//origin.x = Median(xVerts, xVerts.size());
		//origin.y = Median(yVerts, yVerts.size());
		//origin.z = Median(zVerts, zVerts.size());

		//position.x = origin.x;
		//position.y = origin.y;
		//position.z = origin.z;

		//localPosition.x = origin.x;
		//localPosition.y = origin.y;
		//localPosition.z = origin.z;

		transform = glm::translate(transform, glm::vec3(origin.x, origin.y, origin.z));
		// 
		//transform = glm::scale(transform, glm::vec3(1, 1, 1));
	}

	float Median(std::vector<float> v, int n)
	{
		// Sort the vector
		std::sort(v.begin(), v.end());

		// Check if the number of elements is odd
		if (n % 2 != 0)
			return (float)v[n / 2];

		// If the number of elements is even, return the average
		// of the two middle elements
		return (float)(v[(n - 1) / 2] + v[n / 2]) / 2.0;
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
		if (childObject == nullptr) return;

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

