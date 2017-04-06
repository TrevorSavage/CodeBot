#include "SceneObject.h"
#include <iostream>

SceneObject::SceneObject(std::string name){
	this->name = name;
	clearTransforms();
}
SceneObject::~SceneObject(){}

void SceneObject::clearTransforms() {
	translation = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
}

std::string SceneObject::getName() {
	return name;
}

glm::vec3 SceneObject::getTranslation() {
	return translation;
}

void SceneObject::setTranslation(glm::vec3 newVal) {
	translation = newVal;
}

glm::vec3 SceneObject::getRotation() {
	return rotation;
}

glm::vec3 SceneObject::getScale() {
	return scale;
}

void SceneObject::translateBy(glm::fvec3 transVal) {
	translation += transVal;
}

void SceneObject::rotateBy(glm::fvec3 rotVal) {
	std::cout << "rotation " << rotation[0] << rotation[1] << rotation[2] << std::endl;
	rotation += rotVal;
	std::cout << "rotation " << rotation[0] << rotation[1] << rotation[2] << std::endl;
}

void SceneObject::scaleBy(glm::fvec3 scaleVal) {
	scale *= scaleVal;
}

void SceneObject::draw(glm::mat4 parentTransform) {}