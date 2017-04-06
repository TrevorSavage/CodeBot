#pragma once
#include <vector>
#include "glm\glm.hpp"
#include <iostream>

class HudNode
{
public:
	HudNode(glm::vec2 p, glm::vec2 s, int id);
	~HudNode();

	glm::vec2 getPos();
	glm::vec2 getSize();
	HudNode* getNext();
	std::string getName();
	void setNext(HudNode* next);
	glm::vec2 getInputCenter();
	glm::vec2 getOutputCenter();
	int getNumTicks();
	void setNumTicks(int newVal);

	//this function is run whenever this node is connected to the execution path
	virtual void onRun() = 0;
	//returns a 1 if input selected, 2 if output, 3 if node itself, 0 if none
	virtual int checkCollision(int x, int y);
	//draws the node to the screen
	virtual void draw();
	//used when a node is being dragged around
	void moveNode(int x, int y);
	int getId();

protected:

	struct ConnectionNode {
		HudNode* parent;
		int offsetX;
		int offsetY;

		ConnectionNode(HudNode* p, int offX, int offY) { parent = p; offsetX = offX; offsetY = offY; }

		//all connectionNodes will be 20px by 20px
		const int size = 20;

		//returns the upper-left corner of the connection node
		glm::vec2 getPos() { 
			return parent->getPos() + glm::vec2(offsetX, offsetY); 
		}

		bool checkCollision(int x, int y) {
			glm::vec2 pos = getPos();
			if (x >= pos[0] && x < pos[0] + size && y >= pos[1] && y < pos[1] + size) {
				return true;
			}
			else return false;
		}
	};

	std::string name;
	ConnectionNode* execIn;
	ConnectionNode* execOut;

private:
	glm::vec2 pos;
	glm::vec2 size;
	int numTicks;
	int id;

	HudNode* next;
};

