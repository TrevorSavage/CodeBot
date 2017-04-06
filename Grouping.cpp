#include "Grouping.h"
#include <iostream>


Grouping::Grouping(std::string name) : SceneObject(name){}

Grouping::Grouping(std::string name, std::vector<SceneObject*> initObjs) : SceneObject(name) {
	objects = initObjs;
}

Grouping::~Grouping()
{
	for (int i = 0; i < objects.size(); i++) {
		delete(objects[i]);
	}
}

void Grouping::rotateChildrenBy(glm::vec3 rotAmt) {
	for (SceneObject* obj : getObjects()) {
		obj->rotateBy(rotAmt);
	}
}

std::vector<SceneObject*> Grouping::getObjects() {
	return objects;
}

SceneObject* Grouping::getObject(std::string name) {
	for (SceneObject* p : objects) {
		if (p->getName() == name) {
			return p;
		}
	}
}

void Grouping::addObject(SceneObject* obj) {
	objects.push_back(obj);
}

void Grouping::removeObject(std::string name) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->getName() == name) {
			delete objects[i];
			objects.erase(objects.begin() + i);
		}
	}
}

void Grouping::draw(glm::mat4 clipTransform) {
	glm::mat4 groupTransform = Transformer::getMatrix(getTranslation(), getRotation(), getScale());

	glm::mat4 totalTransform = clipTransform*groupTransform;
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->draw(totalTransform);
	}
}
