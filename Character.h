#pragma once
#include "RenderedObject.h"

enum Direction{left, right, up, down};

class Character :
	public RenderedObject
{
public:
	Character(std::string name, ObjectMesh* m);
	Character(std::string name, ObjectMesh* m, Texture* t);
	~Character();

	Direction getDirection();
	glm::vec2 getPos();
	void setPos(glm::vec2 newVal);
	bool getIsDead();
	void setIsDead(bool newVal);
	void turnLeft();
	void turnRight();
	void moveForward();
	void goToIdleState();
	void goToAttackState();
	void goToDeadState();
	void reset();
private:
	glm::vec2 levelPos;
	Direction direction;
	ObjectMesh* idleMesh;
	ObjectMesh* attackMesh;
	ObjectMesh* deadMesh;
	bool isDead;
};

