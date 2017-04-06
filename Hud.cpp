#include "Hud.h"
#include "StartNode.h"
#include "MoveForwardNode.h"
#include "libraries\glew\glew.h"
#include "libraries\freeGlut\freeglut.h"
#include "Transformer.h"
#include <iostream>


Hud::Hud()
{
	this->width = Transformer::windowWidth;
	this->height = Transformer::windowHeight / 3;
	start = new StartNode(glm::vec2(0, 0), glm::vec2(120, 60), requestNodeId());
	nodes.insert(nodes.begin(), start);
	selectedIn = NULL;
	selectedOut = NULL;
	draggedNode = NULL;
	lineEndpoint = glm::vec2(0, 0);
	isMessageShowing = false;
	message = "You didn't reach the goal. Try again.";
}


Hud::~Hud()
{
	delete start;
}

HudNode* Hud::getStartNode() {
	return start;
}

void Hud::setMessage(std::string newVal) {
	message = newVal;
}

void Hud::setIsMessageShowing(bool newVal) {
	isMessageShowing = newVal;
}

bool Hud::hasSelectedConnection() {
	if (selectedIn != NULL || selectedOut != NULL) {
		return true;
	}
	else return false;
}

void Hud::updateLineConnection(int x, int y) {
	lineEndpoint = glm::vec2(x, y);
}

void Hud::draw() {
	// draw the bounding box of our HUD
	int windowWidth = Transformer::windowWidth;
	int windowHeight = Transformer::windowHeight;
	this->width = windowWidth;
	this->height = windowHeight/3;

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, windowWidth, windowHeight, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	//draw each node in our vector of nodes
	glColor3f(0.6, 0.6, 0.6); // light grey
	glRectf(0, 0, width, height);

	for (int i = nodes.size() - 1; i >= 0; i--) {
		nodes[i]->draw();
	}

	//draw the in-progress connection line if it exists
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	if (selectedIn != NULL) {
		glm::vec2 startPoint = selectedIn->getInputCenter();
		glBegin(GL_LINES);
		glVertex2f(startPoint[0], startPoint[1]);
		glVertex2f(lineEndpoint[0], lineEndpoint[1]);
		glEnd();
	}
	else if (selectedOut != NULL) {
		glm::vec2 startPoint = selectedOut->getOutputCenter();
		glBegin(GL_LINES);
			glVertex2f(startPoint[0], startPoint[1]);
			glVertex2f(lineEndpoint[0], lineEndpoint[1]);
		glEnd();
	}

	//draw all existing connection lines
	for (HudNode* n : nodes) {
		if (n->getNext() != NULL) {
			glm::vec2 startPoint = n->getOutputCenter();
			glm::vec2 endPoint = n->getNext()->getInputCenter();
			glBegin(GL_LINES);
				glVertex2f(startPoint[0], startPoint[1]);
				glVertex2f(endPoint[0], endPoint[1]);
			glEnd();
		}
	}

	//draw the pop-up message if it is visible
	if (isMessageShowing) {
		glColor3f(0.8f, 0.8f, 0.8f); // very light grey
		glRectf(windowWidth / 4, windowHeight / 4, 3 * windowWidth / 4, 3 * windowHeight / 4);

		glColor3f(0.0f, 0.0f, 0.0f);
		int messageLength = (message.size() * 8);
		int textStartX = -messageLength / 2 + windowWidth / 2;
		int textStartY = windowHeight / 2;
		glRasterPos2d(textStartX, textStartY);
		for (int i = 0; i < message.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, message[i]);
		}
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);

}

void Hud::onMousePressed(int x, int y) {
	if (isMessageShowing) {
		isMessageShowing = false;
		return;
	}
	for (HudNode* n : nodes) {
		int collision = n->checkCollision(x, y);
		if (collision == 1) {
			//collided w/ input node
			if (selectedIn == NULL) {
				if (selectedOut == NULL) {
					//if no other inputs/outputs currently selected, start drawing a line from this input
					selectedIn = n;
					lineEndpoint = selectedIn->getInputCenter();
				}
				else if (selectedOut == n) {
					//can't connect a node to itself
					selectedOut = NULL;
				}
				else {
					//if we have an output node selected, connect the two and stop drawing line
					selectedOut->setNext(n);
					selectedOut = NULL;
				}
			}
			else {
				//if we have an input already selected, break the link
				selectedIn = NULL;
			}
			return;
		}
		else if (collision == 2) {
			//collided w/ output node
			if (selectedOut == NULL) {
				if (selectedIn == NULL) {
					//if no other inputs/outputs currently selected, start drawing a line from this input
					selectedOut = n;
					lineEndpoint = selectedOut->getOutputCenter();
				}
				else if (selectedIn == n) {
					//can't connect a node to itself
					selectedIn = NULL;
				}
				else {
					//if we have an input node selected, connect the two and stop drawing line
					n->setNext(selectedIn);
					selectedIn = NULL;
				}
			}
			else {
				//if we have an output already selected, break the link
				selectedOut = NULL;
			}
			return;
		}
		else if(collision == 3) {
			if (selectedIn == NULL && selectedOut == NULL) {
				draggedNode = n;
			}
			else {
				selectedIn = NULL;
				selectedOut = NULL;
			}
			return;
		}
	}

	//if we get here, we did not collide w/ anything
	selectedIn = NULL;
	selectedOut = NULL;
}

void Hud::onMouseReleased(int x, int y) {
	//std::cout << "the mouse was released!\n";
	draggedNode = NULL;
}

void Hud::onMouseDragged(int x, int y, glm::vec2 last) {
	if (draggedNode == NULL) return;
	int offsetX = x - last[0];
	int offsetY = y - last[1];
	draggedNode->moveNode(offsetX, offsetY);
}

void Hud::addNode(HudNode* newNode) {
	nodes.insert(nodes.begin(), newNode);
}

void Hud::deleteNode(HudNode* deleteVal) {
	if (start->getId() == deleteVal->getId()) {
		return;
	}

	HudNode* current = start;
	while (current->getNext() != NULL) {
		if (current->getNext()->getId() == deleteVal->getId()) {
			current->setNext(NULL);
			break;
		}
		current = current->getNext();
	}
	for (int i = 0; i < nodes.size(); ++i) {
		if (nodes[i]->getId() == deleteVal->getId()) {
			std::swap(nodes[nodes.size()-1], nodes[i]);
			std::cout << "we popped it back. what is going on\n";
			nodes.pop_back();
		}
	}
	//delete deleteVal;
}

void Hud::deleteNodeAt(glm::vec2 pos) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->checkCollision(pos[0], pos[1]) > 0) {
			deleteNode(nodes[i]);
			return;
		}
	}
}

int Hud::requestNodeId() {
	int returnVal = currentNodeId;
	currentNodeId++;
	return returnVal;
}
