#pragma once
#include "HudNode.h"
#include "Game.h"
#include "libraries\freeGlut\freeglut.h"
#include <string>
#include <iostream>

class RepeatNextNode :
	public HudNode
{
private:
	int repetitions;
	ConnectionNode* plus;
	ConnectionNode* minus;
public:
	RepeatNextNode(glm::vec2 p, glm::vec2 s, int id) : HudNode(p, s, id) {
		name = "Repeat Next";
		repetitions = 1;
		minus = new ConnectionNode(this, 2, getSize()[1] - 22);
		plus = new ConnectionNode(this, getSize()[0] - 22, getSize()[1] - 22);
		setNumTicks(repetitions);
	}
	virtual ~RepeatNextNode() {};

	int getReps() {
		return repetitions;
	}

	void onRun() {
		if (repetitions > 0) {
			getNext()->onRun();
		}
	}

	int checkCollision(int x, int y) {
		std::cout << "collided\n";
		int collision = HudNode::checkCollision(x, y);
		if (collision == 3) {
			if (plus->checkCollision(x, y)) {
				if (repetitions < 10) {
					repetitions++;
					setNumTicks(repetitions);
				}
			}
			else if (minus->checkCollision(x, y)) {
				if (repetitions > 1) {
					repetitions--;
					setNumTicks(repetitions);
				}
			}
		}

		return collision;
	}

	void draw() {
		HudNode::draw();

		// Draw +/- buttons
		glColor3f(1.0f, 0.1f, 0.1f); //red
		glm::vec2 p = plus->getPos();
		int s = plus->size;
		glRecti(p[0], p[1], p[0] + s, p[1] + s);

		glColor3f(0.1f, 0.1f, 1.0f); //blue
		p = minus->getPos();
		s = minus->size;
		glRecti(p[0], p[1], p[0] + s, p[1] + s);

		//display + text
		glColor3f(0.0f, 0.0f, 0.0f);
		int textStartX = plus->getPos()[0] - 8 / 2 + plus->size / 2;
		int textStartY = plus->getPos()[1] + plus->size * 2 / 2;
		glRasterPos2d(textStartX, textStartY);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '+');

		//display - text
		textStartX = minus->getPos()[0] - 8 / 2 + minus->size / 2;
		textStartY = minus->getPos()[1] + minus->size * 1/2;
		glRasterPos2d(textStartX, textStartY);
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '-');

		//display the current repetitions
		std::string numString = std::to_string(repetitions);

		textStartX = getPos()[0] - (numString.size() * 8) / 2 + getSize()[0] / 2;
		textStartY = getPos()[1] + getSize()[1] * 9/10;
		glRasterPos2d(textStartX, textStartY);
		for (int i = 0; i < numString.size(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, numString[i]);
		}
	}
};
