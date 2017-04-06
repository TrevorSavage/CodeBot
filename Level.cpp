#include "Level.h"
#include <iostream>


Level::Level(std::vector<std::vector<int>> grid, RenderedObject* tile)
{
	gridArray = grid;
	terrainTile = tile;
	isWon = false;

	ObjectMesh* m = new ObjectMesh("C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/obj/terrainCube.obj");
	Texture* t = new Texture("C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/textures/wallTex.png");
	wallTile = new RenderedObject("wallTile", m, t);

	m = new ObjectMesh("C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/obj/terrainCube.obj");
	t = new Texture("C:/Users/Trevor/Documents/Visual Studio 2015/Projects/openGl_ModelingProject/modelingTestProject/assets/textures/finishTex.png");
	finishTile = new RenderedObject("finish", m, t);
}


Level::~Level()
{
}

void Level::setGridArray(std::vector<std::vector<int>> newVal) {
	gridArray = newVal;
}

bool Level::getIsWon() {
	return isWon;
}

void Level::setIsWon(bool newVal) {
	isWon = newVal;
}

void Level::setPlayerStartPos(glm::vec2 newVal) {
	playerStartPos = newVal;
	playerPawn->translateBy(glm::vec3(newVal[0], 0, newVal[1]));
	playerPawn->setPos(newVal);
}

void Level::movePlayerForward() {
	Direction playerDir = playerPawn->getDirection();
	glm::vec2 intendedPos = playerPawn->getPos();

	switch (playerDir) {
	case left: intendedPos[0]--; break;
	case right: intendedPos[0]++; break;
	case up: intendedPos[1]--; break;
	case down: intendedPos[1]++; break;
	default: break;
	}

	int tileVal = gridArray[intendedPos[1]][intendedPos[0]];
	if (tileVal == 1) {
		playerPawn->moveForward();
	}
	else if (tileVal == 2) {
		std::cout << "we hit a wall at " << intendedPos[0] << " " << intendedPos[1] << std::endl;
		return;
	}
	else if (tileVal == 3) {
		playerPawn->moveForward();
		isWon = true;
	}
	else if (tileVal == 0) {
		std::cout << "we fell in a hole\n";
		playerPawn->moveForward();
		playerPawn->goToDeadState();
	}
}

void Level::draw(glm::mat4 parentTransform) {
	terrainTile->clearTransforms();
	int sizeY = gridArray.size();
	int sizeX = 0;
	if (sizeY > 0) {
		sizeX = gridArray[0].size();
	}
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			if (gridArray[i][j] == 1) {
				terrainTile->draw(parentTransform);
				terrainTile->translateBy(glm::vec3(1, 0, 0));
			}
			else if (gridArray[i][j] == 2) {
				terrainTile->draw(parentTransform);
				wallTile->setTranslation(terrainTile->getTranslation());
				wallTile->translateBy(glm::vec3(0, 0.84, 0));
				wallTile->draw(parentTransform);
				terrainTile->translateBy(glm::vec3(1, 0, 0));
			}
			else if (gridArray[i][j] == 3) {
				finishTile->setTranslation(terrainTile->getTranslation());
				finishTile->draw(parentTransform);
			}
			else {
				terrainTile->translateBy(glm::vec3(1, 0, 0));
			}
		}
		terrainTile->translateBy(glm::vec3(-sizeX, 0, 1));
	}
	playerPawn->draw(parentTransform);
}

void Level::reset() {
	playerPawn->reset();
}
