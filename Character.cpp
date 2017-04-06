#include "Character.h"
#include "Transformer.h"
#include <iostream>



Character::Character(std::string name, ObjectMesh* m) : RenderedObject(name, m){
	idleMesh = m;
	attackMesh = m;
	deadMesh = m;
	direction = right;
	isDead = false;
}
Character::Character(std::string name, ObjectMesh* m, Texture* t) : RenderedObject(name, m, t) {
	idleMesh = m;
	attackMesh = m;
	deadMesh = m;
	direction = right;
	isDead = false;
}
Character::~Character(){}

Direction Character::getDirection() {
	return direction;
}

glm::vec2 Character::getPos() {
	return levelPos;
}

void Character::setPos(glm::vec2 newVal) {
	levelPos = newVal;
}

bool Character::getIsDead() {
	return isDead;
}

void Character::setIsDead(bool newVal) {
	isDead = newVal;
}

void Character::turnLeft() {
	switch (direction) {
	case left: direction = down; break;
	case right: direction = up; break;
	case up: direction = left; break;
	case down: direction = right; break;
	default: direction = direction; break;
	}
	rotateBy(glm::vec3(0, 90, 0));
}

void Character::turnRight() {
	switch (direction) {
	case left: direction = up; break;
	case right: direction = down; break;
	case up: direction = right; break;
	case down: direction = left; break;
	default: break;
	}
	rotateBy(glm::vec3(0, -90, 0));
}

void Character::moveForward() {
	switch (direction) {
	case left: levelPos[0]--; break;
	case right: levelPos[0]++; break;
	case up: levelPos[1]--; break;
	case down: levelPos[1]++; break;
	default: break;
	}
	std::cout << "pos is " << levelPos[0] << " " << levelPos[1] << std::endl;
	glm::vec4 transVal = glm::vec4(1.0, 0.0, 0.0, 1.0)*Transformer::getRotationMatrix(-getRotation());
	translateBy(transVal);
}

void Character::goToIdleState() {
	setMesh(idleMesh);
}

void Character::goToAttackState() {
	setMesh(attackMesh);
}

void Character::goToDeadState() {
	setMesh(deadMesh);
	isDead = true;
}

void Character::reset() {
	clearTransforms();
	setPos(glm::vec2(1,1));
	direction = right;
	setTranslation(glm::vec3(levelPos[0], 0, levelPos[1]));
	setIsDead(false);
}
