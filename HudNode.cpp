#include "HudNode.h"
#include "libraries\glew\glew.h"
#include "libraries\freeGlut\freeglut.h"
#include "Transformer.h"



HudNode::HudNode(glm::vec2 pos, glm::vec2 size, int id){
	execIn = new ConnectionNode(this, 2, 2);
	execOut = new ConnectionNode(this, size[0]-22, 2);
	this->pos = pos;
	this->size = size;
	this->id = id;
	this->next = NULL;
	this->numTicks = 1;
}
HudNode::~HudNode(){
	if (execIn != NULL) delete execIn;
	if (execOut != NULL) delete execOut;
}

glm::vec2 HudNode::getPos() {
	return pos;
}

glm::vec2 HudNode::getSize() {
	return size;
}

HudNode* HudNode::getNext() {
	return next;
}

void HudNode::setNext(HudNode* newVal) {
	next = newVal;
}

std::string HudNode::getName() {
	return name;
}

int HudNode::checkCollision(int x, int y) {
	if (x >= pos[0] && x < pos[0] + size[0]) {
		if (y >= pos[1] && y < pos[1] + size[1]) {
			if (execIn != NULL && execIn->checkCollision(x, y)) return 1;
			else if (execOut != NULL && execOut->checkCollision(x, y)) return 2;
			else return 3;
		}
	}
	else return 0;
}

void HudNode::draw() {
	// draw the bounding box of our node
	glColor3f(0.8f, 0.8f, 0.8f); // very light grey
	glRecti(pos[0], pos[1], pos[0] + size[0], pos[1] + size[1]);

	// Draw input/output
	glColor3f(1.0f, 1.0f, 1.0f); //white
	if (execIn != NULL) {
		glm::vec2 p = execIn->getPos();
		int s = execIn->size;
		glRecti(p[0], p[1], p[0] + s, p[1] + s);
	}
	if (execOut != NULL) {
		glm::vec2 p = execOut->getPos();
		int s = execOut->size;
		glRecti(p[0], p[1], p[0] + s, p[1] + s);
	}

	glColor3f(0.0f, 0.0f, 0.0f);
	int textStartX = pos[0] - (name.size() * 8) / 2 + size[0] / 2;
	int textStartY = pos[1] + size[1] * 2/3;
	glRasterPos2d(textStartX, textStartY);
	for (int i = 0; i < name.size(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, name[i]);
	}
}

void HudNode::moveNode(int x, int y) {
	pos[0] = pos[0] + x;
	pos[1] = pos[1] + y;

	int maxX = Transformer::windowWidth - size[0];
	int minX = 0;
	int maxY = Transformer::windowHeight/3 - size[1];
	int minY = 0;
	if (pos[0] < minX) { pos[0] = minX; }
	if (pos[0] > maxX) { pos[0] = maxX; }
	if (pos[1] < minY) { pos[1] = minY; }
	if (pos[1] > maxY) { pos[1] = maxY; }
}

glm::vec2 HudNode::getInputCenter() {
	int x = execIn->getPos()[0] + execIn->size / 2;
	int y = execIn->getPos()[1] + execIn->size / 2;
	return glm::vec2(x, y);
}

glm::vec2 HudNode::getOutputCenter() {
	int x = execOut->getPos()[0] + execOut->size / 2;
	int y = execOut->getPos()[1] + execOut->size / 2;
	return glm::vec2(x, y);
}

int HudNode::getNumTicks() {
	return numTicks;
}
void HudNode::setNumTicks(int newVal) {
	numTicks = newVal;
}

int HudNode::getId() {
	return id;
}


